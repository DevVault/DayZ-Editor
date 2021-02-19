class EditorObjectMarker: EditorMarker
{	
	protected Editor m_Editor;
	protected EditorObject m_EditorObject;

	protected ref DragHandler m_DragHandler;
	
	void EditorObjectMarker(EditorObject editor_object)
	{
		EditorLog.Trace("EditorObjectMarker");
		m_EditorObject = editor_object;
		m_Editor = GetEditor();
		
		m_EditorObject.OnObjectSelected.Insert(EditorObjectSelected);
		m_EditorObject.OnObjectDeselected.Insert(EditorObjectDeselected);	
	}
	
	void ~EditorObjectMarker()
	{
		delete m_DragHandler;
	}
	
	void EditorObjectSelected(EditorObject data) 
	{		
		Select();
	}
	
	void EditorObjectDeselected(EditorObject data) 
	{
		Deselect();
	}
		
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{		
		// ignores the object if you are placing
		if (m_Editor.IsPlacing()) return false;
		
		
		switch (button) {
			
			case MouseState.LEFT: {
				
				// We want to Toggle selection if you are holding control
				if (KeyState(KeyCode.KC_LCONTROL)) {
					m_Editor.ToggleSelection(m_EditorObject);
					return true;
				} 
				
				// allows multiple objects to be dragged
				if (m_EditorObject.IsSelected()) {
					thread CheckDragBounds(x, y);
					return true;
				}
				
				if (!KeyState(KeyCode.KC_LSHIFT)) {
					m_Editor.ClearSelection();
				}
				
				m_Editor.SelectObject(m_EditorObject);
				
				thread CheckDragBounds(x, y);
				return false;
			}
			
			case MouseState.MIDDLE: {
				EditorCamera camera = GetEditor().GetCamera();
				vector pos = m_EditorObject.GetPosition();
				pos[1] = camera.GetPosition()[1];
				camera.SetPosition(pos);
				return true;
			}
		}
		
		return super.OnMouseButtonDown(w, x, y, button);
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		switch (button) {
			
			case MouseState.RIGHT: {
				
				if (!m_EditorObject.IsSelected() && !KeyState(KeyCode.KC_LSHIFT)) {
					m_Editor.ClearSelection();
				}
				
				m_Editor.SelectObject(m_EditorObject);
				
				if (EditorHud.CurrentMenu) {
					delete EditorHud.CurrentMenu;
				}
				
				EditorHud.CurrentMenu = new EditorPlacedContextMenu(x, y);
				
				return true;
			}
			
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	void Select() 
	{
		m_LayoutRoot.SetAlpha(MARKER_ALPHA_ON_SHOW);
	}
	
	void Highlight()
	{
		m_LayoutRoot.SetAlpha(MARKER_ALPHA_ON_SHOW);
	}
	
	void Deselect() 
	{
		m_LayoutRoot.SetAlpha(MARKER_ALPHA_ON_HIDE);
	}
	
	bool IsSelected() 
	{
		return m_EditorObject.IsSelected();
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (!IsSelected()) {
			Highlight();
			if (m_EditorObject.GetListItem()) {
				m_EditorObject.GetListItem().Highlight();
			}
		}
		
		return super.OnMouseEnter(w, x, y);
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (!IsSelected()) {
			Deselect();
			if (m_EditorObject.GetListItem()) {
				m_EditorObject.GetListItem().Deselect();
			}
		}
		
		return super.OnMouseLeave(w, enterW, x, y);
	}
	
	private const int DRAG_THRESHOLD = 5;
	private void CheckDragBounds(int x, int y)
	{
		while (GetMouseState(MouseState.LEFT) & MB_PRESSED_MASK) {
			int c_x, c_y;
			GetMousePos(c_x, c_y);
			
			int dist_x = Math.AbsInt(x - c_x);
			int dist_y = Math.AbsInt(y - c_y);
			
			if (dist_x + dist_y > DRAG_THRESHOLD) {
				GetEditor().SelectObject(m_EditorObject);
				m_DragHandler.OnDragStart();
				return;
			}
			
			Sleep(10);
		}
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		m_Editor.CommandManager.ObjectPropertiesCommand.Execute(this, null);
		
		return true;
	}
	
	EditorObject GetEditorObject() 
	{ 
		return m_EditorObject; 
	}
	
	DragHandler GetDragHandler() 
	{
		return m_DragHandler; 
	}
}