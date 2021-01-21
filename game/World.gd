extends Node3D

func _ready():

	# Spawn ECS entities
	var godex = true
	# Element to spawn
	var spawn_count = 10000

	# The spawned element uses or not use the mesh. 
	var no_mesh = false

	# Want to spawn debris
	var debris = true
	# Want to spawn random transform
	var random_transform = true

	for i in range(spawn_count):
		if godex == false:
			if debris:
				spawn_node_debris(
					Vector3(randf_range(-10, 10), randf_range(-10, 10), randf_range(-10, 10)),
					Vector3(randf_range(-20, 20), randf_range(0, 20), randf_range(-20, 20)),
					no_mesh)
			if random_transform:
				spawn_node_random_transform(no_mesh)

		else:
			if debris:
				spawn_entity_debris(
					Vector3(randf_range(-10, 10), randf_range(-10, 10), randf_range(-10, 10)),
					Vector3(randf_range(-20, 20), randf_range(0, 20), randf_range(-20, 20)),
					no_mesh)
			if random_transform:
				spawn_entity_random_transform(no_mesh)


@onready var physical_debris_prefab = load("res://Prefabs/Debris.tscn").instance()
@onready var physical_debris_prefab_no_mesh = load("res://Prefabs/DebrisNoMesh.tscn").instance()
@onready var physical_RT_prefab = load("res://Prefabs/RandomTransform.tscn").instance()
@onready var physical_RT_prefab_no_mesh = load("res://Prefabs/RandomTransformNoMesh.tscn").instance()

func spawn_entity_debris(velocity: Vector3, position: Vector3, no_mesh: bool):
	var entity_id
	if no_mesh:
		entity_id = ECS.get_active_world().create_entity_from_prefab(physical_debris_prefab_no_mesh)
	else:
		entity_id = ECS.get_active_world().create_entity_from_prefab(physical_debris_prefab)

	var debris = ECS.get_active_world().get_entity_component(entity_id, "Debris")
	debris.velocity = velocity
	var trans = ECS.get_active_world().get_entity_component(entity_id, "TransformComponent")
	trans.transform.origin = position

func spawn_entity_random_transform(no_mesh: bool):
	if no_mesh:
		ECS.get_active_world().create_entity_from_prefab(physical_RT_prefab_no_mesh)
	else:
		ECS.get_active_world().create_entity_from_prefab(physical_RT_prefab)


@onready var physical_RT_node = load("res://Nodes/RandomTransform.tscn")
@onready var physical_RT_node_no_mesh = load("res://Nodes/RandomTransformNoMesh.tscn")
@onready var physical_debris_node = load("res://Nodes/DebrisCpp.tscn")
@onready var physical_debris_node_no_mesh = load("res://Nodes/DebrisCppNoMesh.tscn")

func spawn_node_debris(velocity: Vector3, position: Vector3, no_mesh: bool):
	var debris
	if no_mesh:
		debris = physical_debris_node_no_mesh.instance()
	else:
		debris = physical_debris_node.instance()
	add_child(debris)
	debris.velocity = velocity
	debris.transform.origin = position

func spawn_node_random_transform(no_mesh: bool):
	var rt
	if no_mesh:
		rt = physical_RT_node_no_mesh.instance()
	else:
		rt = physical_RT_node.instance()
	add_child(rt)
