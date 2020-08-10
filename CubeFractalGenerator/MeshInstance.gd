extends MeshInstance


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var st: SurfaceTool


# Called when the node enters the scene tree for the first time.
func _ready():
	st = SurfaceTool.new()
	make_cube(4, Vector3(0, 0, 50))
	make_cube(4, Vector3(4, 0, 50))
	st.generate_normals()
	mesh = st.commit()


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func make_cube(cube_size: float, position: Vector3):
	var offset = cube_size / 2
	
	st.begin(Mesh.PRIMITIVE_TRIANGLES)
	
	st.add_vertex(Vector3(-offset, offset, offset) + position) # Front top left 0
	st.add_vertex(Vector3(offset, offset, offset) + position) # Front top right 1
	st.add_vertex(Vector3(-offset, -offset, offset) + position) # Front bottom left 2
	st.add_vertex(Vector3(offset, -offset, offset) + position) # Front bottom right 3
	
	st.add_vertex(Vector3(-offset, offset, -offset) + position) # Back top left 4
	st.add_vertex(Vector3(offset, offset, -offset) + position) # Back top right 5
	st.add_vertex(Vector3(-offset, -offset, -offset) + position) # Back bottom left 6
	st.add_vertex(Vector3(offset, -offset, -offset) + position) # Back bottom right 7
	
	# Front face:
	st.add_index(0)
	st.add_index(1)
	st.add_index(3)
	
	st.add_index(3)
	st.add_index(2)
	st.add_index(0)
	
	# Back face:
	st.add_index(7)
	st.add_index(5)
	st.add_index(4)
	
	st.add_index(4)
	st.add_index(6)
	st.add_index(7)
	
	# Left face:
	st.add_index(2)
	st.add_index(6)
	st.add_index(4)
	
	st.add_index(4)
	st.add_index(0)
	st.add_index(2)
	
	# Right face:
	st.add_index(1)
	st.add_index(5)
	st.add_index(7)
	
	st.add_index(7)
	st.add_index(3)
	st.add_index(1)
	
	# Top face:
	st.add_index(0)
	st.add_index(4)
	st.add_index(5)
	
	st.add_index(5)
	st.add_index(1)
	st.add_index(0)
	
	# Bottom face:
	st.add_index(7)
	st.add_index(6)
	st.add_index(2)
	
	st.add_index(2)
	st.add_index(3)
	st.add_index(7)
