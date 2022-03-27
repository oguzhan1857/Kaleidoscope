kaleidoscope  = __import__("kaleidoscope")
database      = __import__("database")

import ui

class SkinChanger(ui.Menu):
    def __init__(self, title):
        ui.Menu.__init__(self, title)
        self.init_instances()
        self.build()

    def init_instances(self):
        self.player = kaleidoscope.GetPlayer()

    def on_skin_change(self, value):
        self.player.ChangeSkin(value)
        
    def build(self):
        model    = self.player.GetModelHash()
        skinList = database.GetSkinList(model)
        self.skin_combo = ui.ComboBox.create(self, "Current Skin", 0, skinList, self.on_skin_change)

    def OnUpdate(self):
        pass


skinChanger = SkinChanger("SkinChanger")