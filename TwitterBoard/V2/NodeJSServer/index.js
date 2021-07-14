#!/usr/bin/env node
const bearerToken = '';
const websocketPort = 2323;
var doTwitter = true;
var doTwitterAgainTime = 0;
process.on('unhandledRejection', function(err, promise) {
    console.error('Unhandled rejection (promise: ', promise, ', reason: ', err, ').');
	console.log(err.code)
	if (err.code == 429){
		console.log("rate limit hit! whoops")
		doTwitterAgainTime = err.rateLimit["reset"];
		var diff = err.rateLimit["reset"]-(Date.now()/1000);
		console.log(diff," seconds left");
		doTwitter = false;
	}
});
//// Twitter stuff /// 
const { TwitterApi } = require('twitter-api-v2'); // npm i twitter-api-v2
const twitterClient = new TwitterApi(bearerToken).readOnly;
var tweetIDs = []; // tweets previously seen
var theTweets = []; // tweets to send to MCUs
var wait_time = 30000; // THIS IS IN MS
var had_tweets = false;
var searchTerm = "Latitude2021";
var userID = "954820947013439489";
var lastGotMentions = 0;
var lastGotSearch = -1;
var tweetToSend = {};
// search twitter for tweets
var tweetSearch = async function(search_str){
	lastGotSearch = 0  
	const results = await twitterClient.v2.search(searchTerm,{'expansions':'author_id'}); // search for 'searchTerm' in tweets, expand the "author_id" to an array of users
	const data = results._realData.data; // array of tweets
	const users = results._realData.includes.users; // array of users
	data.forEach((tweet, index) => { // iterate tweets 
		if (tweetIDs.indexOf(tweet.id) !== -1) { // check if its been seen
			//console.log("seen this one");
		} else { // new tweet
			var thisTweet = {} // empty object
			tweetIDs.push(tweet.id); // push to the seen array
			thisTweet["text"] = tweet.text; // set the tweet text
			var aut_id = tweet.author_id; // get the author id
			console.log(aut_id); 
			users.forEach((usr,idx) => { // iterate the users
				if (usr.id == aut_id) { // match the author id
					thisTweet["user"] = usr.username; // setup the username
				} else {
					thisTweet["user"] = "unknown user"; // this should never happen
				}
			});
			theTweets.push(thisTweet) // add to the array
			lastGotSearch += 1
		}
	});
};
// get tweets which mention a user
var getMentions = async function(){
	console.log("getting mentions")
	lastGotMentions = 0
	const res = await twitterClient.v2.get('users/'+userID+'/mentions',{ 
		expansions:['author_id'],
		'tweet.fields':['attachments','author_id','text'],
		'user.fields':['description','id','location','name','username','verified'],
	});
	//console.log(res);
	//console.log(res.includes.users);
	const data = res.data;
	const users = res.includes.users;
	data.forEach((tweet,index) => {
		if (tweetIDs.indexOf(tweet.id) !== -1) { // check if its been seen
			//console.log("seen this one");
		} else { // new tweet
			var thisTweet = {}
			tweetIDs.push(tweet.id);
			thisTweet["text"] = tweet.text;
			var aut_id = tweet.author_id;
			console.log(aut_id);
			users.forEach((usr,idx) => {
				if (usr.id == aut_id) {
					thisTweet["user"] = usr.username;
				} else {
					thisTweet["user"] = "unknown user";
				}
			});
			theTweets.push(thisTweet)
			lastGotMentions += 1
			//console.log(thisTweet)
		} 
		
		
	});
	console.log("finished getting mentions, there are ",theTweets.length," in the queue ",)
	//console.log(theTweets)
}
getMentions() // do this here so we have half a chance of making the first API call before any websocket clients connect


/// WebSocket stuff /// 
const WebSocket = require('ws'); // npm i ws
const wss = new WebSocket.Server({ port: websocketPort });
function noop() {}; // empty callback for when connections time out
var CLIENTS = []; // list of clients connected

function heartbeat() {
  this.isAlive = true; // keep alive func
}

// creates unique ID for each websocket client
wss.getUniqueID = function () {
    function s4() {
        return Math.floor((1 + Math.random()) * 0x10000).toString(16).substring(1);
    }
    return s4() + s4() + '-' + s4();
};
// Broadcast message to all clients
function sendAll (message) {
	//console.log("SENDALL CALLED, ",message);
	clients.forEach((value,ind) => {
        value.ws.send(message);
		//console.log("sent to ",key);
    });
}
function tweetAll(){
	var numSent = 0; 
	for (const [key, value] of Object.entries(CLIENTS)) { // iterate clients
 		value.ws.send(JSON.stringify(tweetToSend)); // turn to string and send
		numSent += 1;
	}
	console.log("sent ",tweetToSend," to ",numSent," clients");
}
wss.on('connection', function connection(ws) {
	console.log("CONNECTIION"); // on new connection
	ws.id = wss.getUniqueID(); // make uid
	ws.isAlive = true; // is just connected so assume alive.
	CLIENTS.push({"id":ws.id,"ws":ws}); // push onto clients array
	console.log("New Client Added ",ws.id); 
	var reply = {"command":"getID","val":ws.id,}; // tell client it's own ID (just to confirm connection)
	ws.send(JSON.stringify(reply)) // send it
	ws.on('message', function incoming(message) {
		message = message.toString(); // its an array of byte so make it a string
		
		message = message.replace(/[^A-Za-z 0-9 \.,\?""!@#\$%\^&\*\(\)-_=\+;:<>\/\\\|\}\{\[\]`~]*/g, ''); // strip any non-ascii chars or jibberish
		if (message.indexOf('{') !== 0){ // make sure the message is valid JSON
			message = message.substring(message.indexOf('{')) // try and make it valid if it isnt.. 
		}
		var obj = JSON.parse(message); // parse the JSON 
		console.log(obj)
		if(obj.command === "ping"){ // Pin request
			console.log('got ping request at: ',obj.val) 
			var reply = {"command":"pong","val":obj.val,}; // make JSON reply
			ws.send(JSON.stringify(reply)); // Turn JSON to String and send
		}
		else if (obj.command === "pong"){
			// client replies to heartBeat
			ws.isAlive = true;
			console.log("keeping client ",ws.id," alive");
		}
		else if (obj.command === "get"){
			console.log("got request from ",ws.id);
			var reply = {}
			if (theTweets.length > 0){
				reply = theTweets[0];
				reply["command"] = "tweet";
			}
			else {
				reply["command"] = "notweet";
			}
			ws.send(JSON.stringify(reply));
		}
		else if (obj.command === "insert"){
			console.log("got insert request from ",ws.id);
			console.log(theTweets);
			delete obj.command;
			theTweets.unshift(obj);
			console.log(theTweets);
			var reply = {"command":"insert","val":true};
			ws.send(JSON.stringify(reply));
		}
		else if (obj.command === "skip"){
			console.log("got skip request from ",ws.id);
			clearInterval(interval);
			interval = setInterval(intervalFunction, wait_time);
		}
		else {
			console.log("UNKNOWN COMMAND")
		}
	});		
});
 // the "loop" i guess
var intervalFunction = function() { 
	if (wait_time < 20000) wait_time = 20000;
	console.log("INTERVAL");
    for (const [key, value] of Object.entries(CLIENTS)) {
		if (value.ws.isAlive === false){
		// if the client did not respond last time		
			console.log(value.ws.id," is dead");
			var wsID = value.ws.id;
			//console.log(CLIENTS[value.ws.id]);
			CLIENTS.forEach((cl,idx) => {
				if (cl.id == wsID) {
					delete CLIENTS[idx];
					console.log("deleted client ",wsID);
				}
			});
			//console.log(CLIENTS[value.ws.id]);
			return value.ws.terminate();
		} else {
			// the client did respond last time so ping them again
			value.ws.isAlive = false;
			//console.log(value.ws.isAlive)
			var toSend = {"command":"ping","val":value.ws.id,}; // make JSON reply
			value.ws.send(JSON.stringify(toSend));
		}
	}
	if (theTweets.length > 0 && Object.keys(CLIENTS).length > 0){ // be sure we have a tweet, and at least 1 client
		had_tweets = true;
		tweetToSend = theTweets.shift(); // get the first tweet 
		tweetToSend["command"] = "tweet"; // so the parser knows what type of command it is
		tweetAll();
	}
	if (doTwitter == true){
		console.log("twitter get enabled, doing that");
		if (theTweets.length == 0 && Object.keys(CLIENTS).length > 0){ // no tweets but have clients
			if (had_tweets == false){ // didn't have tweets last time we ran either :(
				var toSend = {"command":"pattern"} // make run pattern
				for (const [key, value] of Object.entries(CLIENTS)) { // iterate clients
					value.ws.send(JSON.stringify(toSend)); // turn to string and send
				}
			}
			if (lastGotMentions == 0){ // no one loves us, 
				tweetSearch() // do a search 
			}
			if (lastGotSearch == 0){ // we triedsearch and got nothing :( SAD!
				tweetIDs = [] // clear known tweets so we show ones we've seen
			}
			
		}		
		getMentions() // get the mentions again
	} else {
		console.log("twitter get disabled, doing that");
		if (doTwitterAgainTime-(Date.now()/1000) < 0){
			console.log("rate limit passed, trying again");
			doTwitter = true;
		} else {
			if (theTweets.length == 0){
				var noTweet = {};
				noTweet["user"] = "ERROR";
				noTweet["text"] = "WE ARE BEING RATE LIMITED!!!!";
				theTweets.push(noTweet);
				console.log("added ratelimit tweet");
			} else {
				console.log("theres already something to send");
				console.log("there are ",doTwitterAgainTime-(Date.now()/1000)," secs til i contact twitter again");
			}
		}
	}
		
}

var interval = setInterval(intervalFunction, wait_time); // set everything off
