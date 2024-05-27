extends MeshInstance3D

const speed = 8.0;

# Called when the node enters the scene tree for the first time.
func _ready():
    cast_shadow = GeometryInstance3D.SHADOW_CASTING_SETTING_DOUBLE_SIDED
    pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
var neptune_rot = 0.0;
func _process(delta):
    if neptune_rot > 360.0:
        neptune_rot = 0.0;
    else:
        neptune_rot += speed*delta;
    rotation_degrees = Vector3(0,neptune_rot,0)
