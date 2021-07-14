const wsAddr = 'ws://serv.squatnet.co.uk:2323';
const serPort = 'COM7';
var theUser = "";
var theTweet = "";
function parseMessage(message){
	console.log("p msg");
	message = message.toString(); // its an array of byte so make it a string
	message = message.replace(/[^A-Za-z 0-9 \.,\?""!@#\$%\^&\*\(\)-_=\+;:<>\/\\\|\}\{\[\]`~]*/g, ''); // strip any non-ascii chars or jibberish
	if (message.indexOf('{') !== 0){ // make sure the message is valid JSON
		message = message.substring(message.indexOf('{')) // try and make it valid if it isnt.. 
	}
	var obj = JSON.parse(message); // parse the JSON 
	if (obj.command === "ping"){
		var rep = {"command":"pong"};
		console.log("reply");
		ws.send(JSON.stringify(rep));
	} else if (obj.command === "tweet"){
		theUser = obj.user;
		theTweet = obj.text;
		writeSerial("tweet");
	} else if (obj.command === "pattern"){
		writeSerial("pattern");
	}
	// add pattern supprt etc
}

// websocket stuff //
const WebSocket = require('ws');
const ws = new WebSocket('ws://serv.squatnet.co.uk:2323');
ws.on('message', function incoming(data) {
  console.log(data);
  parseMessage(data);
});
// serial stuff // 
const SerialPort = require('serialport')
const port = new SerialPort(serPort, {
  baudRate: 9600
})
// Open errors will be emitted as an error event
port.on('error', function(err) {
  console.log('Error: ', err.message)
})
function writeSerial(what) { // wip
	console.log("writing serial ",what);
	var toSend = "";
	if (what === "tweet"){
		toSend = "%$%"+theUser+"$£$"+theTweet+"$%$";
	} else if (what === "pattern"){
		toSend = "%^%pat$%$";
	}	
	console.log(toSend);
	port.write(toSend, function(err) {
		if (err) {
			return console.log('Error on write: ', err.message)
		} else {
			console.log('message written')
		}
	});
	
	// add pattern supprt etc
}



