extends CanvasLayer

signal generate_fractal(ratio, iterations)
signal material_chosen(material)

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	$MenuButton.get_popup().connect("id_pressed", self, "_on_item_pressed")


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

var text = ""



func _on_RatioEdit_text_changed():
	if $RatioLabel/RatioEdit.text.is_valid_integer() or $RatioLabel/RatioEdit.text == "":
		text = $RatioLabel/RatioEdit.text
	else:
		$RatioLabel/RatioEdit.text = text
		$RatioLabel/RatioEdit.cursor_set_column(text.length())


func _on_IterationEdit_text_changed():
	if $IterationLabel/IterationEdit.text.is_valid_integer() or $IterationLabel/IterationEdit.text == "":
		text = $IterationLabel/IterationEdit.text
	else:
		$IterationLabel/IterationEdit.text = text


func _on_Button_pressed():
	if $RatioLabel/RatioEdit.text == "" or $IterationLabel/IterationEdit.text == "":
		$Popup.popup_centered()
	elif int($IterationLabel/IterationEdit.text) > 7:
		$Confirmation.popup_centered()
	else:
		emit_signal("generate_fractal", int($RatioLabel/RatioEdit.text), int($IterationLabel/IterationEdit.text))

func _on_item_pressed(id):
	var item_name = $MenuButton.get_popup().get_item_text(id)
	emit_signal("material_chosen", item_name)


func _on_Confirmation_confirmed():
	emit_signal("generate_fractal", int($RatioLabel/RatioEdit.text), int($IterationLabel/IterationEdit.text))
