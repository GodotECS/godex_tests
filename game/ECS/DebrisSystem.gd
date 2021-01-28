extends System

func _prepare():
	with_databag(ECS.FrameTime, IMMUTABLE)
	with_component(ECS.TransformComponent, MUTABLE)
	with_component(ECS.Debris_gd, MUTABLE)


func _for_each(frame_time, transform_com, debris_com):
	var distance_to_center = transform_com.transform.origin * -1.0
	debris_com.velocity += distance_to_center * frame_time.delta
	transform_com.transform.origin += debris_com.velocity * frame_time.delta 
