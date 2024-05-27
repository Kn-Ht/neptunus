extends Button

var tree
var root

# Called when the node enters the scene tree for the first time.
func _ready():
    tree = get_tree()
    root = tree.root
    var b_opts = root.get_node("menu/button_container/btn_settings")
    var b_exit = root.get_node("menu/button_container/btn_exit")
    
    b_opts.connect("pressed", options)
    b_exit.connect("pressed", exit)

    
func options():
    pass
    
func exit():
    # TODO: ask user before quiting
    get_tree().quit()        
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
    pass
