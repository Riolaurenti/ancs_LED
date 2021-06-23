#!/usr/bin/env node
console.log("Hello World");
const WebSocket = require('ws'); // npm i ws
const wss = new WebSocket.Server({ port: 2323 });
function noop() {}; // empty callback for when connections time out
var CLIENTS = []; // list of clients connected

function heartbeat() {
  this.isAlive = true; // keep alive func (actually not used)
}
// checks clients are connected
const interval = setInterval(() => {
    console.log("INTERVAL");
    for (const [key, value] of Object.entries(CLIENTS)) {
		if (value.ws.isAlive === false){
		// if the client did not respond last time		
			console.log(value.ws.id," is dead");
			var wsID = value.ws.id;
			//console.log(CLIENTS[value.ws.id]);
			CLIENTS.forEach((cl,idx) => { // updated to work with array instead of object
				if (cl.id == wsID) {
					delete CLIENTS[idx];
					console.log("deleted client ",wsID)
				}
			});
			//console.log(CLIENTS[value.ws.id]);
			return value.ws.terminate();
		} else {
			// the client did respond last time so ping them again
			value.ws.isAlive = false;
			//console.log(value.ws.isAlive)
			var toSend = {"command":"ping","val":value.ws.id,}; // make JSON reply
			value.ws.send(JSON.stringify(toSend))
		}
	}
}, 30000); // run every 30s
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
const { TwitterApi } = require('twitter-api-v2'); // npm i twitter-api-v2
const twitterClient = new TwitterApi('sniiiiiiip. no credentials here').readOnly;
var tweetIDs = []; // tweets previously seen
var theTweets = []; // tweets to send to MCUs

// search twitter for tweets
var tweetSearch = async function(search_str){
	const results = await twitterClient.v2.search('autoAV',{'expansions':'author_id'}); // search for "autoAV in tweets, expand the "author_id" to an array of users
	console.log(results); // 10 tweets 
	const data = results._realData.data; // array of tweets
	const user = results._realData.includes.users; // array of users
	console.log(data); 
	console.log(user);
	var myResult  = {}; 
	data.forEach((twt, index) => { // iterate tweets 
		if (tweetIDs.indexOf(twt.id) !== -1) { // check if its been seen
			console.log("seen this one");
		} else { // new tweet
			tweetIDs.push(twt.id);
			// get the author_id, and get the user data from the other array
			// based on the author_id 
			//then make a nicely packaged JSON object and add it to theTweets array
		}
	});
};
// get the mentions for user 954820947013439489 (@ancs_autoav)
var getMentions = async function(){
	const res = await twitterClient.v2.get('users/954820947013439489/mentions',{
		expansions:['author_id'],
		'tweet.fields':['attachments','author_id','text'],
		'user.fields':['description','id','location','name','username','verified'],
	}); 
	console.log(res);
	console.log(res.includes.users);
	const data = res.data; // An array of the tweets
	// [{"id":tweetID,"text":tweetText,"author_id":tweet_author_id},{"id":tweetID,"text":tweetText,"author_id":tweet_author_id}] // 
	const users = res.includes.users; // an array of the users 
	//  [{"id":user_id,"location":user_bio_location,"username":user_@_handle,"description":user_bio,"name":user_display_name,"verified":false}]
	data.forEach((tweet,index) => { // iterate the array of tweets
		var thisTweet = {} // create object for this tweet
		if (tweetIDs.indexOf(tweet.id) !== -1) { // check if its been seen
			console.log("seen this one");
		} else { // new tweet
			tweetIDs.push(tweet.id); // add it to the list of seen tweets
			thisTweet["text"] = tweet.text; // get the tweet text
			var aut_id = tweet.author_id; 
			console.log(aut_id);
			thisTweet["user"] = ""; // init empty, just in case for some reason there is no record of the user
			users.forEach((usr,idx) => { // iterate array of users 
				if (usr.id == aut_id) { // if this user id matches the author_id of the tweet
					thisTweet["user"] = usr.username; // set the username
				} else {
					// do nothing
				}
			});
		}
		console.log(thisTweet)
		theTweets.push(thisTweet) // push this entry onto the back of theTweets array
	});
	console.log(theTweets)
}


//// websockety stuffs ////
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
		if(obj.command === "ping"){ // Ping request (not fully implemented) 
			console.log('got ping request at: ',obj.val)  
			var reply = {"command":"pong","val":obj.val,}; // make JSON reply
			ws.send(JSON.stringify(reply)); // Turn JSON to String and send
		}
		else if (obj.command === "pong"){ // client replies to keep alive
			ws.isAlive = true; 
			console.log("keeping client ",ws.id," alive");
		}
	});
});
getMentions();
