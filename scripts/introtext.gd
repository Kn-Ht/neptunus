extends RichTextLabel

# Reveal the intro text slowly

var text_len = 0
var enter_btn: Button

# Called when the node enters the scene tree for the first time.
func _ready():
	enter_btn = get_parent().get_node("enter_btn")
	enter_btn.hide()
	enter_btn.connect("pressed", func(): SceneTransition.change_scene("res://scenes/game_submarine.tscn"))
	text_len = text.length()
	visible_characters = 0
 
var passed_time = 0.0
const reveal_time_s = 10.0
const reveal_btn_time_s = reveal_time_s + 1

func _process(delta):
	if passed_time < reveal_btn_time_s:
		passed_time += delta
		visible_characters = (passed_time / reveal_time_s) * text_len
	else:
		enter_btn.show()
