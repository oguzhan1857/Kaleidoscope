kaleidoscope  = __import__("kaleidoscope")

import ui
from targetselector import TargetSelector

class Orbwalker(ui.Menu):
    def __init__(self, title):
        ui.Menu.__init__(self, title)
        self.init_instances()
        self.build()

    def init_instances(self):
        self.player = kaleidoscope.GetPlayer()
        self.cursor = kaleidoscope.HudManager.GetInstance().GetWorldCursor()
        self.input  = kaleidoscope.HudManager.GetInstance().GetInputLogic()
        self.targetSelector = TargetSelector("TargetSelector")
        
        self.last_aa_tick = 0.0
        self.last_mv_tick = 0.0
        self.last_wl_tick = 0.0

    def build(self):
        self.draw_range_checkbox = ui.Checkbox.create(self, "Draw Range", True)
        self.extra_delay_slider  = ui.SliderFloat.create(self, "Extra Delay" ,  0.018, 0.000, 0.100)
        self.extra_windup_slider = ui.SliderFloat.create(self, "Extra Windup",  0.011, 0.000, 0.100)
        
    def can_attack(self):
        if(self.player.CanAttack() == False):
            return False
        
        attack_delay = self.player.GetAttackDelay()
        extra_delay  = self.extra_delay_slider.get_value()
        ping         = kaleidoscope.NetClient.GetInstance().GetPingSec() / 2.0
        return attack_delay + self.last_aa_tick + extra_delay + ping < kaleidoscope.GetTime()

    def can_move(self):
        return self.player.GetWindup() + self.last_aa_tick + self.extra_windup_slider.get_value() < kaleidoscope.GetTime()
    
    def move_humanizer(self):
        if(self.last_wl_tick < kaleidoscope.GetTime()):
            self.last_wl_tick = kaleidoscope.GetTime() + 0.08
            cursor_pos = self.cursor.GetPos().ToScreen()
            self.cursor.OnRightClickMove(int(cursor_pos.x), int(cursor_pos.y), 0, 1, 1)

    def orb_walk(self, target):
        if(target == None):
            self.move_humanizer()
            return
        
        if(self.can_attack()):
            self.last_aa_tick = kaleidoscope.GetTime()
            target_w2s = target.GetPos().ToScreen()
            self.input.IssueClick(0, 1, 0, int(target_w2s.x), int(target_w2s.y), 0)
            self.input.IssueClick(1, 1, 0, int(target_w2s.x), int(target_w2s.y), 0)
        else:
            if(self.can_move() and self.last_wl_tick < kaleidoscope.GetTime()):
                self.last_mv_tick = kaleidoscope.GetTime()
                self.move_humanizer()

    def OnUpdate(self):
        if(kaleidoscope.IsPressed(32)):
            range  = self.player.GetAttackRange() + self.player.GetBound() + 45.0
            target = self.targetSelector.get_target(range)
            self.orb_walk(target)
    
    def OnRender(self):
        if(self.draw_range_checkbox.get_value() == True):
            range  = self.player.GetAttackRange() + self.player.GetBound()
            color  = kaleidoscope.Vector4(0.89, 0.12, 0.48, 1.00)
            kaleidoscope.DrawCircle3D(self.player.GetPos(), range, color, 1.3)

orbwalker = Orbwalker("OrbWalker")