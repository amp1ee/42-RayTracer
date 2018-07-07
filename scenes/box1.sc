
plane { pnt: 0,4,0; dir: 0,1,0; clr: 128,128,128 rfl: 0.8  }
plane { pnt: 0,-4,0; dir: 0,-1,0; clr: 128,128,128 rfl: 0.8 }
plane { pnt: 0,0,4; dir: 0,0,-1; clr: 128,128,128 rfl: 0.8 }
plane { pnt: 0,0,-4; dir: 0,0,1; clr: 128,128,128  rfl: 0.8 }
plane { pnt: 4,0,0; dir: 1,0,0; clr: 128,128,128 rfl: 0.8  }
plane { pnt: -4,0,0; dir: -1,0,0; clr: 128,128,128 rfl: 0.8  }

sphere { pnt: 0.2,0,0.2; rds: 0.2; clr: 255,0,0 }
sphere { pnt: 0,0.2,0; rds: 0.2; clr: 0,255,0 }
sphere { pnt: 0,0,-0.2; rds: 0.2; clr: 0,0,255 }
sphere { pnt: -0.2,0,0.2; rds: 0.2; clr: 255,0,255 }

light { pnt: 2,0,-2; int: 0.3; }
light { pnt: -2,0,-2; int: 0.3; }
light { pnt: 2,0,2; int: 0.3; }
light { pnt: -2,0,2; int: 0.3; }

camera { dir: 5,-10,0; pnt: -1,0,-4; }
