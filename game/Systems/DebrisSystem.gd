extends System

const speed = 1.0

func _prepare():
	with_databag(ECS.FrameTime, IMMUTABLE)
	with_component(ECS.TransformComponent, MUTABLE)
	with_component(ECS.Debris_gd, MUTABLE)


func _for_each(frame_time, transform, debris):
	var distance_to_center = transform.transform.origin * -1.0
	debris.velocity += distance_to_center * speed * frame_time.delta
	transform.transform.origin += debris.velocity * frame_time.delta
