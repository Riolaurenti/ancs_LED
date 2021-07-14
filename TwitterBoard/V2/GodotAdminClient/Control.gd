extends Control

var ws = null # empty var for WebSocketClient
var url = "ws://serv.squatnet.co.uk:2323"
var port = 2323
var tweetScene = preload("res://Tweet.tscn")
var patternScene = preload("res://Pattern.tscn")
var disconScene = preload("res://DisconPan.tscn")
var logVar = []

func prnt(val): ## alternate print
	print(val)
	logVar.push_back(str(val))

func parser(packet): # parses JSON received from server
	# check packet is actually JSON
	if typeof(packet) != 18:
		# exit if not
		prnt("Wrong data type")
		return
	# get ping reply
	if packet.command == "ping":
		sendWS(to_json({"command":"pong"}))
	elif packet.command == "pong":
		var cTime = OS.get_unix_time()
		$Control/ResponseLabel.text = "PONG! Roundtrip took "+str(cTime-int(packet.val))+" s"
	elif packet.command == "getID":
		prnt("WE REGISTERED WITH ID "+packet.val)
		$Label.text = "connected with ID "+packet.val
		sendWS(to_json({"command":"get"}))
	elif packet.command == "tweet":
		prnt("GOT TWEET FROM "+packet.user)
		prnt(packet.text)
		var newTweet = tweetScene.instance()
		newTweet.setup(packet.user,packet.text)
		for i in $TweetContainer.get_children():
			i.finish()
		$TweetContainer.add_child(newTweet,true)
	elif packet.command == "insert":
		prnt("Insert done success")
		$Control2/Panel/VBoxContainer/LineEdit.text = ""
		$Control2/Panel/VBoxContainer/TextEdit.text = ""
		$Control2.hide()
		$Control/ResponseLabel.text = "Insert success"
	elif packet.command == "pattern":
		prnt("Pattern")
		var newPtn = patternScene.instance()
		for i in $TweetContainer.get_children():
			i.finish()
		$TweetContainer.add_child(newPtn,true)
	else:
		prnt("CANT PARSE PACKET")
		prnt(to_json(packet))

#### websockets stuff ###
func _connect(): ## connect websockets
	set_process(true)
	ws = WebSocketClient.new() # Init WebSocket
	ws.connect("connection_established", self, "_connection_established") # connect Callbacks
	ws.connect("connection_closed", self, "_connection_closed") # connect Callbacks
	ws.connect("connection_error", self, "_connection_error") # Connect Callbacks
	prnt("Connecting to " + url)
	ws.connect_to_url(url) # Do the connection

func _connection_established(protocol): # Called on succesful connection to server
	prnt("Connected")
func _connection_closed(m): # called on server closed
	prnt(m)
	set_process(false)
	ws = null 
	prnt("Start timer and try reconnect")
	$Timer.start()
	var newP = disconScene.instance()
	newP.setup($Timer)
	for i in $TweetContainer.get_children():
			i.finish()
	$TweetContainer.add_child(newP,true)
	
func _connection_error(): # called when client disconnects abruptly
	prnt("Connection error")
	set_process(false)
	ws = null 
	prnt("Start timer and try reconnect")
	$Timer.start()

func sendWS(mess): ## abstraction for messaging. safe.
	if ws == null:
		return
	if ws.get_peer(1).is_connected_to_host():
		ws.get_peer(1).put_var(mess)
		prnt("Sending message "+mess)
	else:
		set_process(false)
		ws = null 
		prnt("Start timer and try reconnect")
		$Timer.start()

func _on_Timer_timeout(): ## handles reconnection
	_connect()
## setup ##
func _ready():
	set_process(false)
	_connect()
## the loop ## 
func _process(_delta): # Process is the main loop, delta is time time last frame in ms
	if ws == null:
		return
	else:
		if ws.get_connection_status() == ws.CONNECTION_CONNECTING || ws.get_connection_status() == ws.CONNECTION_CONNECTED:
			## if we are connecting or connected poll the server
			ws.poll()
		if ws == null:
			return
		if !ws.has_method("get_peer"):
			ws = null
			return
		if ws.get_peer(1).is_connected_to_host():
			## if we are connected check for messages
			if ws.get_peer(1).get_available_packet_count() > 0 :
				## if there are packets waiting get the next one
				var test = ws.get_peer(1).get_packet()
				prnt('recieve %s' % test.get_string_from_ascii ())
				## put it through the parser
				parser(parse_json(test.get_string_from_ascii()))
				




## Menu buttons ## 
func _on_PingBtn_pressed():
	sendWS(to_json({"command":"ping","val":OS.get_unix_time()}))

func _on_NextBtn_pressed():
	sendWS(to_json({"command":"get"}))

func _on_Insert_pressed():
	$Control2.show()
	
func _on_Skip_pressed():
	var mess = {"command":"skip"}
	sendWS(to_json(mess))

## insert message panel buttons ## 
func _on_inserConfirm_pressed():
	if $Control2/Panel/VBoxContainer/LineEdit.text == "":
		$Control2/Panel/VBoxContainer/Label2.text = "You must enter a username"
		return
	if $Control2/Panel/VBoxContainer/TextEdit.text == "":
		$Control2/Panel/VBoxContainer/Label2.text = "You must enter a message"
		return
	var rep = {"command":"insert","user":$Control2/Panel/VBoxContainer/LineEdit.text,"text":$Control2/Panel/VBoxContainer/TextEdit.text}
	sendWS(to_json(rep))
	pass # Replace with function body.

func _on_InsertCancel_pressed():
	$Control2.hide()

func _on_PAttern_pressed():
	sendWS(to_json({"command":"pattern"}))
