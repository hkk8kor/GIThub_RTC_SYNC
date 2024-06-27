
/**
* @PVCONTEXT {PVMODEL}
* @PVLABEL {Start Variant Generation}
*/

// context object of pure::variants
var pv_context = pure_variants();
// check if the calling context is correct
if (pv_context.isModelContext() == false  && pv_context.isEditorContext() == false)
	throw new java.lang.Exception("Invalid invocation context!\n\nInvocation context must be a pure::variants model or a pure::variants editor.\n\n");

/**
* Gets the context project's name.
* @return {String} The project's name.
*/
function getProjectName() {
var project_name = pure_variants().getNameOfContextProject();
return project_name;
}

/**
* Gets the Variant Models of the project.
* @param {String} project_name Name of the project.
* @return {List} List of feature models.
*/
function getVariantModels(project_name) {
var variantmodel_path_list = pure_variants().getVariantModelPaths(project_name);
return variantmodel_path_list;
}

/**
* Gets the root element of the given model.
* @param {IPVModel} model The model.
* @return {IPVElement} The root element.
*/
function getRootElement(model) {
var root_element = model.getRoot();
return root_element;
}

/**
* Changes the selection of a given element in the given variant.
* @param {IPVVariantModel} variantModel The variant description model.
* @param {IPVElement} element The element for which to change the selection.
* @param {Number} newState The new selection state of the element.
*/
function changeSelection(variantModel, element, newState) {
	var operation = pure_variants().changeVariantModel(variantModel);
	var selection = variantModel.getSelectionOfReference(element);
	if (selection != null) {
		operation.changeSelection(element, newState);
	}
	else {
		operation.addSelection(element, newState);
	}
	pure_variants().updateModel(operation);
	pure_variants().saveModel(variantModel)
}

/**
* Set the selection state of the given element to SELECTION explicitly in the given variant
* so that the vdm file is modified to include this selection.
* @param {IPVVariantModel} variantModel The variant description model.
* @param {IPVElement} element The model element.
*/
function SetSelectionState(variantModel, element) {

	var newState = VariantElementState().SELECTION;
	var selection_state = variantModel.getState(element).getSelection();
	if (selection_state == VariantElementState().SELECTION) {
		changeSelection(variantModel, element, newState);
	} /*else if (selection_state == VariantElementState().EXCLUSION) {
	console().println("Element " + element.getName() + " is excluded");
	} else if (selection_state == VariantElementState().NONSELECTION) {
	console().println("Element " + element.getName() + " is not selectable");
	} else if (selection_state == VariantElementState().UNSELECTION) {
	console().println("Element " + element.getName() + " is not selected");
	} else {
	console().println("Element " + element.getName() + " is not selected");
	} */
}

/**
* Get the root element and call the function to retrieve the children  
* and set the selection state
*/
function GetRootElement_Children_Selection(value){
	
	// Get root element of the model 
	var root_element = getRootElement(pure_variants().getContextModel());

	// Get the variant model name
	var Variantmodel = pure_variants().openModel(value)
	console().write("\n Variant Model name :" + Variantmodel + "\n");

	// Set selection state of root element
	SetSelectionState(Variantmodel, root_element);
	GetChildren_SetSelection(Variantmodel, root_element);

}

/**
* Get the children of the Variant Model and call the function to set the Selection State
* @param {IPVVariantModel} variantModel The variant description model.
* @param {IPVElement} element The model element.
*/
function GetChildren_SetSelection(Variantmodel,element) {

	var Childelement_list = getDirectChildren(element);
	var idx = Childelement_list.iterator();
	while (idx.hasNext()) {
		var child_element = idx.next();
		SetSelectionState(Variantmodel, child_element);
		GetChildren_SetSelection(Variantmodel, child_element);
	}
}

/**
* Get the direct children of the given element.
* @param {IPVElement} element The element.
*/
function getDirectChildren(element) {
	var element_list = element.getChildren();
	return element_list;
}

/**
* Get the Variant Models of the project and call the function to retrieve the root element, 
* children of respective variant model and set the Selection
*/
function GetVariantModel_Children_SetSelection(){
	var variant_model_list;
	variant_model_list= getVariantModels(getProjectName());
	var idx = variant_model_list.iterator();
	while (idx.hasNext()) {
		var variant_model = idx.next();
		GetRootElement_Children_Selection(variant_model);
	}
}

/**
* Function to get the path of Feature Model file.
* @param {IPVElement} element The element.
*/
function GetFeatureModelPath() {
	var path = pure_variants().getFeatureModelPaths(getProjectName());
	var idx = path.iterator();
	while (idx.hasNext()) {
		var featureModelFile = idx.next();
		var FeatureModel_path = featureModelFile.split("/");
		FeatureModel_path = FeatureModel_path.slice(0, -1);
		FeatureModel_path = FeatureModel_path.join("/");
	}
	return FeatureModel_path;
}

/**
* Function to Set Selection and call Variant Generator Script.
*/
function SetSelection_VariantGenerator() {

	// Get all the Variant Models, children and set the selection based on the selection type
	GetVariantModel_Children_SetSelection();

	//Get the path in which Featuremodel is present
	var featureModelPath = GetFeatureModelPath();

	console().write("\nStarting Variant Generator Script");

	/** Call the Variant Generator Script
	* cmd.exe /c start --- To start the command prompt 
	* /wait cmd /c  ------ To close the command prompt automatically after pressing a key
	* \"" - \"" ---------- The complete path of VariantGenerator script is enclosed within double 
	* quotes (" ")  so that spaces with in the path is also accepted
	*/
	java.lang.Runtime.getRuntime().exec("cmd.exe /c start /wait cmd /c \"" + featureModelPath + 
	"/scripts/Generate_RB_MS_MMP2_europium_int.bat\"");

	console().write("\nEnd of Script");

}

SetSelection_VariantGenerator();

//https://www.pure-systems.com/pv-update/additions/doc/latest/pv-javascript-guide.pdf