extends Spatial

var dirt = ResourceLoader.load("res://Assets/dirt.png")
var stone = ResourceLoader.load("res://Assets/stone.png")
var netherrack = ResourceLoader.load("res://Assets/netherrack.png")
var blackstone = ResourceLoader.load("res://Assets/blackstone.png")
var cobblestone = ResourceLoader.load("res://Assets/cobblestone.png")

var current_material = stone
var total_blocks

enum direction {UP, DOWN, FRONT, BACK, LEFT, RIGHT, NONE}

signal fractalize(ratio, iterations)


# Called when the node enters the scene tree for the first time.
func _ready():
	pass


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _fractalize(cube, ratio, iterations, build_direction):
	if iterations == 1:
		return
	
	var mainSideLenght = cube.scale.x
	var subSideLength = mainSideLenght / ratio
	var offset = (mainSideLenght + subSideLength)
	var newScale = Vector3(subSideLength, subSideLength, subSideLength)
	
	total_blocks += 12 * ((pow(subSideLength, 2) ) + (subSideLength * (subSideLength - 2)) + pow(subSideLength - 2, 2))
	
	# Top cube:
	if build_direction != direction.DOWN:
		var small_cube = CSGBox.new()
		small_cube.scale = newScale
		small_cube.transform.origin = cube.transform.origin + (offset * Vector3.UP)
		small_cube.material = SpatialMaterial.new()
		small_cube.material.albedo_texture = current_material
		small_cube.material.uv1_scale = newScale
		$Fractal.add_child(small_cube)
		_fractalize(small_cube, ratio, iterations - 1, direction.UP)
	
	# Bottom cube:
	if build_direction != direction.UP:
		var small_cube = CSGBox.new()
		small_cube.scale = newScale
		small_cube.transform.origin = cube.transform.origin + (offset * Vector3.DOWN)
		small_cube.material = SpatialMaterial.new()
		small_cube.material.albedo_texture = current_material
		small_cube.material.uv1_scale = newScale
		$Fractal.add_child(small_cube)
		_fractalize(small_cube, ratio, iterations - 1, direction.DOWN)
	
	# Left cube:
	if build_direction != direction.RIGHT:
		var small_cube = CSGBox.new()
		small_cube.scale = newScale
		small_cube.transform.origin = cube.transform.origin + (offset * Vector3.LEFT)
		small_cube.material = SpatialMaterial.new()
		small_cube.material.albedo_texture = current_material
		small_cube.material.uv1_scale = newScale
		$Fractal.add_child(small_cube)
		_fractalize(small_cube, ratio, iterations - 1, direction.LEFT)
	
	# Right cube:
	if build_direction != direction.LEFT:
		var small_cube = CSGBox.new()
		small_cube.scale = newScale
		small_cube.transform.origin = cube.transform.origin + (offset * Vector3.RIGHT)
		small_cube.material = SpatialMaterial.new()
		small_cube.material.albedo_texture = current_material
		small_cube.material.uv1_scale = newScale
		$Fractal.add_child(small_cube)
		_fractalize(small_cube, ratio, iterations - 1, direction.RIGHT)
	
	# Front cube:
	if build_direction != direction.BACK:
		var small_cube = CSGBox.new()
		small_cube.scale = newScale
		small_cube.transform.origin = cube.transform.origin + (offset * Vector3.FORWARD)
		small_cube.material = SpatialMaterial.new()
		small_cube.material.albedo_texture = current_material
		small_cube.material.uv1_scale = newScale
		$Fractal.add_child(small_cube)
		_fractalize(small_cube, ratio, iterations - 1, direction.FRONT)
	
	# Back cube
	if build_direction != direction.FRONT:
		var small_cube = CSGBox.new()
		small_cube.scale = newScale
		small_cube.transform.origin = cube.transform.origin + (offset * Vector3.BACK)
		small_cube.material = SpatialMaterial.new()
		small_cube.material.albedo_texture = current_material
		small_cube.material.uv1_scale = newScale
		$Fractal.add_child(small_cube)
		_fractalize(small_cube, ratio, iterations - 1, direction.BACK)

func _on_Controls_generate_fractal(ratio, iterations):
	emit_signal("fractalize", ratio, iterations)
	
#	var cubes = $Fractal.get_children()
#	for cube in cubes:
#		cube.queue_free()
#
#	total_blocks = 0
#
#	var baseSize = pow(ratio, iterations)
#	total_blocks += 2 * ((pow(baseSize, 2) ) + (baseSize * (baseSize - 2)) + pow(baseSize - 2, 2))
#	print("Base cube size: " + str(baseSize) + " blocks")
#	var baseScale = Vector3(baseSize, baseSize, baseSize)
#	var baseCube = CSGBox.new()
#	baseCube.scale = baseScale
#	baseCube.material = SpatialMaterial.new()
#	baseCube.material.albedo_texture = current_material
#	baseCube.material.uv1_scale = baseScale
#	baseCube.transform.origin = Vector3(0, 0, 0)
#	$Fractal.add_child(baseCube)
#
#	var time_before = OS.get_ticks_usec()
#	_fractalize(baseCube, ratio, iterations, direction.NONE)
#	var time_taken = OS.get_ticks_usec() - time_before
#	print ("Fractalizing took " + str(time_taken) + "us")
#
#	print("Total blocks (a little over): " + str(total_blocks))
#	print("Stacks: " + str(total_blocks / 64))


func _on_Controls_material_chosen(material):
	match material:
		"Stone":
			current_material = stone
		"Dirt":
			current_material = dirt
		"Netherrack":
			current_material = netherrack
		"Blackstone":
			current_material = blackstone
		"Cobblestone":
			current_material = cobblestone
