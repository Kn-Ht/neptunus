extends Node3D


# Called when the node enters the scene tree for the first time.
func _ready():
    var play_btn = get_node("button_container/btn_play")
    play_btn.connect("pressed", func():
        SceneTransition.change_scene("res://scenes/introscreen.tscn"))
    pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
    pass
