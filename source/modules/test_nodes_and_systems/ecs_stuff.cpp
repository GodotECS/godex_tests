#include "ecs_stuff.h"

void random_teleport_system(Query<const RandomTeleport, TransformComponent> p_query) {
	while (p_query.is_done() == false) {
		auto [tag, transf] = p_query.get();

		transf->get_transform_mut().origin = Vector3(
				Math::random(-10.0, 10.0),
				Math::random(-10.0, 10.0),
				Math::random(-10.0, 10.0));

		p_query.next();
	}
}

void debris_system(const FrameTime *p_frame_time, Query<Debris, TransformComponent> p_query) {
	while (p_query.is_done() == false) {
		auto [debris, transf] = p_query.get();

		const Vector3 distance_to_center = transf->get_transform().origin * -1.0;
		debris->velocity += distance_to_center * p_frame_time->get_delta();
		transf->get_transform_mut().origin += debris->velocity * p_frame_time->get_delta();

		p_query.next();
	}
}
