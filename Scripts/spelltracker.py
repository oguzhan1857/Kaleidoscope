kaleidoscope  = __import__("kaleidoscope")
import ui
import math
from spell import Spell

class SpellTracker(ui.Menu):
    def __init__(self, title):
        ui.Menu.__init__(self, title)
        self.init_instances()
        self.build()

    def init_instances(self):
        self.Q = Spell(0)
        self.W = Spell(1)
        self.E = Spell(2)
        self.R = Spell(3)

    def build(self):
        self.bar_size_x   = ui.SliderInt.create(self, "Bar Size X", 32,  0, 200)
        self.bar_size_y   = ui.SliderInt.create(self, "Bar Size Y", 8,   0, 200)
        self.bar_pos_x    = ui.SliderInt.create(self, "Bar Pos  X", 127, 0, 200)
        self.bar_pos_y    = ui.SliderInt.create(self, "Bar Pos  Y", 72,  0, 200)
        self.bar_offset_x = ui.SliderInt.create(self, "Offset   X", 45,  0, 200)

    def OnUpdate(self):
        if self.Q.can_use():
            kaleidoscope.AddLog("q learned")
        else:
            kaleidoscope.AddLog(f"q remain: {math.ceil(self.Q.get_cd_remain())}")


    #auto cooldown_percent = cooldown_remain / cs->get_cooldown() * 100.0f;
    def OnRender(self):
        bar_size_x_value   = self.bar_size_x.get_value()
        bar_size_y_value   = self.bar_size_y.get_value()
        bar_pos_x_value    = self.bar_pos_x.get_value()
        bar_pos_y_value    = self.bar_pos_y.get_value()
        bar_offset_x_value = self.bar_offset_x.get_value()

        if self.Q.can_use():
            green_color = kaleidoscope.Vector4(0.0, 1.0, 0.0, 1.0)
            enemy_pos   = kaleidoscope.GetPlayer().GetPos().ToScreen()
            bar_pos     = kaleidoscope.Vector2(enemy_pos.x - bar_pos_x_value + bar_offset_x_value * 0, enemy_pos.y + bar_pos_y_value)
            bar_size    = kaleidoscope.Vector2(bar_size_x_value, bar_size_y_value)
            kaleidoscope.DrawBar2D(bar_pos, bar_size, 0.0, green_color, "")
        else:
            pink_color  = kaleidoscope.Vector4(0.89, 0.12, 0.48, 1.00)
            enemy_pos   = kaleidoscope.GetPlayer().GetPos().ToScreen()
            bar_pos     = kaleidoscope.Vector2(enemy_pos.x - bar_pos_x_value + bar_offset_x_value * 0, enemy_pos.y + bar_pos_y_value)
            bar_size    = kaleidoscope.Vector2(bar_size_x_value, bar_size_y_value)
            cooldown_percent = self.Q.get_cd_remain() / self.Q.get_cooldown() * 100
            kaleidoscope.DrawBar2D(bar_pos, bar_size, cooldown_percent, pink_color, "")


        #color     = kaleidoscope.Vector4(0.0, 1.0, 0.0, 1.0) if cooldown_remain == 0 else kaleidoscope.Vector4(0.89, 0.12, 0.48, 1.00)
        #enemy_pos = enemy.GetPos().ToScreen()
        #bar_pos   = kaleidoscope.Vector2(enemy_pos.x - bar_pos_x_value + bar_offset_x_value * index, enemy_pos.y + bar_pos_y_value)
        #bar_size  = kaleidoscope.Vector2(bar_size_x_value, bar_pos_y_value)
        #kaleidoscope.DrawBar2D(bar_pos, bar_size, cooldown_percent, color, cooldown_text)


spelltracker = SpellTracker("SpellTracker")