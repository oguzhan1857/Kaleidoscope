windowmanager = __import__("windowmanager")

class Component:
    def __init__(self, label):
        self.hwnd = None
        self.register_component(label)

    def register_component(self, label):
        self.hwnd = windowmanager.Register(self, label)

    def add_child(self, hwnd):
        self.hwnd.AddChild(hwnd)

    def OnKeyDown(self, key):
        pass

    def OnKeyUp(self, key):
        pass

    def OnDoubleClick(self):
        pass

    def OnUpdate(self):
        pass

    def OnRender(self):
        pass


class Menu(Component):
    def __init__(self, label):
        Component.__init__(self, label)
    
    def register_component(self, label):
        self.hwnd = windowmanager.RegisterMenu(self, label)


class Text(Component):
    def __init__(self, label):
        Component.__init__(self, label)

    def register_component(self, label):
        self.hwnd = windowmanager.RegisterText(self, label)

    @staticmethod
    def create(parent, label):
        instance = Text(label)
        if(parent != None):
            parent.add_child(instance)
        return instance

    def set_text(self, text):
        self.hwnd.SetText(text)

    def get_text(self):
        return self.hwnd.GetText()


class SliderInt(Component):
    def __init__(self, label):
        Component.__init__(self, label)

    @staticmethod
    def create(parent, label, value, min, max):
        instance = SliderInt(label)
        instance.set_value(value)
        instance.set_range(min, max)
        if(parent != None):
            parent.add_child(instance.hwnd)
        return instance

    def register_component(self, label):
        self.hwnd = windowmanager.RegisterSliderInt(self, label)

    def get_value(self):
        return self.hwnd.GetValue()

    def set_value(self, value):
        self.hwnd.SetValue(value)

    def set_range(self, min, max):
        self.hwnd.SetRange(min, max)


class SliderFloat(Component):
    def __init__(self, label):
        Component.__init__(self, label)

    @staticmethod
    def create(parent, label, value, min, max):
        instance = SliderFloat(label)
        instance.set_value(value)
        instance.set_range(min, max)
        if(parent != None):
            parent.add_child(instance.hwnd)
        return instance

    def register_component(self, label):
        self.hwnd = windowmanager.RegisterSliderFloat(self, label)

    def get_value(self):
        return self.hwnd.GetValue()

    def set_value(self, value):
        self.hwnd.SetValue(value)

    def set_range(self, min, max):
        self.hwnd.SetRange(min, max)


class Checkbox(Component):
    def __init__(self, label):
        Component.__init__(self, label)
        self.event_func = None

    @staticmethod
    def create(parent, label, value, event = None):
        instance = Checkbox(label)
        instance.set_value(value)
        if(event != None):
            instance.event_func = event
        if(parent != None):
            parent.add_child(instance.hwnd)
        return instance

    def register_component(self, label):
        self.hwnd = windowmanager.RegisterCheckbox(self, label)

    def get_value(self):
        return self.hwnd.GetValue()

    def set_value(self, value):
        self.hwnd.SetValue(value)

    def set_change_event(self, event):
        self.event_func = event

    def OnValueChange(self, value):
        if(self.event_func):
            self.event_func(value)


class ComboBox(Component):
    def __init__(self, label):
        Component.__init__(self, label)
        self.event_func = None

    @staticmethod
    def create(parent, label, index, data, event=None):
        instance = ComboBox(label)
        instance.set_data(data)
        instance.set_index(index)
        if(event != None):
            instance.event_func = event
        if(parent != None):
            parent.add_child(instance.hwnd)
        return instance

    def register_component(self, label):
        self.hwnd = windowmanager.RegisterComboBox(self, label)

    def get_index(self):
        return self.hwnd.GetIndex()

    def set_index(self, index):
        self.hwnd.SetIndex(index)

    def set_data(self, list):
        self.hwnd.SetData(list)

    def OnValueChange(self, index):
        if(self.event_func):
            self.event_func(index)