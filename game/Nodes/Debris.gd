extends Node3D

const speed = 1.0
var velocity := Vector3()

func _process(delta):
	var distance_to_center = transform.origin * -1.0
	velocity += distance_to_center * speed * delta
	transform.origin += velocity * delta
