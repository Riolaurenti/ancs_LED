extends Panel


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var timer

# Called when the node enters the scene tree for the first time.
func setup(timerNode):
	print(timerNode)
	timer = timerNode
func _ready():
	print(timer)
	$ProgressBar.value = timer.time_left
	$ProgressBar.max_value = timer.wait_time
	$ProgressBar.min_value = 0
	pass # Replace with function body.
func _process(delta):
	if timer:
		$ProgressBar.value = timer.time_left
func finish():
	queue_free()
