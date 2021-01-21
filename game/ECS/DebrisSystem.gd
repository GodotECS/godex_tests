extends System

func _prepare():
	with_databag("FrameTime", IMMUTABLE)
	with_component("TransformComponent", MUTABLE)
	with_component("Debris.gd", MUTABLE)


func _for_each(frame_time, transform_com, debris_com):
	var distance_to_center = transform_com.transform.origin * -1.0
	debris_com.velocity += distance_to_center * frame_time.delta
	transform_com.transform.origin += debris_com.velocity * frame_time.delta 
