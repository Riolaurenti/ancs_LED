#!/usr/bin/env node
console.log("Hello World");
const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 2323 });
function noop() {}; // empty callback for when connections time out
var CLIENTS = []; // list of clients connected

function heartbeat() {
  this.isAlive = true; // keep alive func
}
// checks clients are connected
const interval = setInterval(() => {
    //console.log("INTERVAL");
    for (const [key, value] of Object.entries(CLIENTS)) {
		if (value.ws.isAlive === false){
		// if the client did not respond last time		
			console.log(value.ws.id," is dead");
			var wsID = value.ws.id;
			//console.log(CLIENTS[value.ws.id]);
			delete CLIENTS[value.ws.id];
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
const { TwitterApi } = require('twitter-api-v2');
const twitterClient = new TwitterApi('... SNIP CREDENTIALS ...').readOnly;
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



//// websockety stuffs ////
wss.on('connection', function connection(ws) {
	console.log("CONNECTIION"); // on new connection
	ws.id = wss.getUniqueID(); // make uid
	ws.isAlive = true; // is just connected so assume alive.
	CLIENTS.push({"id":id,"ws":ws}); // push onto clients array
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
	});
});
tweetSearch();
