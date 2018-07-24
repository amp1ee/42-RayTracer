
plane { pnt: 0,2,0; dir: 0,1,0; clr: 128,128,128  }
plane { pnt: 0,-2,0; dir: 0,-1,0; clr: 128,128,128 }
plane { pnt: 0,0,4; dir: 0,0,-1; clr: 128,128,128 }
plane { pnt: 2,0,0; dir: 1,0,0; clr: 255,0,0 }
plane { pnt: -2,0,0; dir: -1,0,0; clr: 0,255,0 }

sphere { pnt: 0.2,0,0.2; rds: 0.5; clr: 0,0,255 rfl: 0.1 }

light { pnt: 1.99,0,-1.99; int: 0.5; }
light { pnt: -1.99,0,-1.99; int: 0.5; }
light { pnt: 1.99,0,1.99; int: 0.5; }
light { pnt: -1.99,0,1.99; int: 0.5; }

camera { dir: 0,0,0; pnt: 0,0,-8; }