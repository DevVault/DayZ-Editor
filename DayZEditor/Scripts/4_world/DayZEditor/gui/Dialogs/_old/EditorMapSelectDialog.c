

/*

class MapSelectDialogController: DialogBaseController
{
	protected TextListboxWidget MapHostListbox;
	
	ref ObservableCollection<string> MapHostListboxData = new ObservableCollection<string>("MapHostListboxData", this);
	string MapHostListboxSelection;
		
	void SetMapSelectDialog(MapSelectDialog select_dialog)
	{
		EditorLog.Trace("MapSelectDialogController::SetMapSelectDialog");
		
		for (int i = 0; i < GetGame().ConfigGetChildrenCount("CfgWorlds"); i++) {
			string name;
			GetGame().ConfigGetChildName("CfgWorlds", i, name);
			if (ExcludedMapItems.Find(name) == -1) {
				MapHostListboxData.Insert(name);
			}
		}
	}
	
	override void PropertyChanged(string property_name)
	{
		EditorLog.Trace("MapSelectDialogController::PropertyChanged");
		
		switch (property_name) {
			
			case "MapHostListboxSelection": {
				/*
				ViewBindingArray view_set = m_DataBindingHashMap.Get(""); // dont ask. just use DebugPrint
				if (view_set) {
					foreach (ViewBinding view: view_set) {
						RoutedUICommand relay_command = view.GetRelayCommand();
						if (relay_command) {
							//relay_command.SetCanExecute(MapHostListboxSelection != string.Empty); todo
						}
					}
				}*/
					
				
				/*
				break;
			}
		}
	}
	/*
	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{		
		if (button != 0) return false; 

		if (w.GetName() == "MapHostListbox") {	
			GetEditor().GetEditorHud().GetModal().Close();
			GetGame().PlayMission(CreateEditorMission(MapHostListboxSelection));
		}
		
		return false;
	}
}


class MapSelectDialog: EditorDialog
{		
	void MapSelectDialog(Widget parent = null) 
	{
		EditorLog.Trace("MapSelectDialog::Init");

		AddContent("DayZEditor/gui/Layouts/dialogs/EditorMapSelector.layout");
		//AddButton("Select", "MapSelectDialogRoutedUICommand"); // add functionality for RelayCommand
		AddButton("Close", CloseDialog);
		MapSelectDialogController.Cast(GetController()).SetMapSelectDialog(this);
	}
	
	
	override typename GetControllerType() {
		return MapSelectDialogController;
	}
	

}*/