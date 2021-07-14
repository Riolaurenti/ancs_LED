extends ColorRect

var user = ""
var text = ""

func setup(usr,txt):
	user = usr
	text = txt
# Called when the node enters the scene tree for the first time.
func _ready():
	if user == "":
		print("Tweet not setup!!")
		queue_free()
	$UserLbl.text = "@"+user
	$TextLbl.text = text
	pass # Replace with function body.

func finish():
	$AnimationPlayer.play("SlideOut")

