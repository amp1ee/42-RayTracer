
plane { pnt: 5,-1,0; dir: 0,1,-0.2; clr: 192,192,192 }


sphere { pnt: 0.2,0,0.2; rds: 0.15; clr: 255,0,0 rfl: 0.99 }
sphere { pnt: -0.2,0,0.2; rds: 0.15; clr: 0,255,0 rfl: 0.99 }


light { pnt: 2,0,-2; int: 0.3; }
light { pnt: -2,0,-2; int: 0.3; }
light { pnt: 2,0,2; int: 0.3; }
light { pnt: -2,0,2; int: 0.3; }

camera { dir: 0,0,0; pnt: 0,0,-2.5; }