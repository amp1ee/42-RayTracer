
plane { pnt: 5,-1,0; dir: 0,1,0; clr: 192,192,192 }
plane { pnt: 5,1,0; dir: 0,1,0; clr: 192,192,192 }
plane { pnt: 0,0,10; dir: 0,0,-1; clr: 0,0,200; }

sphere { pnt: -1,-1,1; rds: 0.3; clr: 192,192,192 }
sphere { pnt: 1,-1,1; rds: 0.3; clr: 192,192,192 }
 
sphere { pnt: 1,1,1; rds: 0.3; clr: 215,192,192 }
sphere { pnt: -1,1,1; rds: 0.3; clr: 192,192,192 }

sphere { pnt: 1,-1,6; rds: 0.3; clr: 192,192,192 }
sphere { pnt: 1,1,6; rds: 0.3; clr: 192,192,192 }

sphere { pnt: -1,-1,6; rds: 0.3; clr: 192,192,192 }
sphere { pnt: -1,1,6; rds: 0.3; clr: 192,192,192 }

sphere { pnt: 0,-0.7,3; rds: 0.2; clr: 255,0,0 }


cylinder { pnt: -1,-1,1; dir: -1,-2,1; rds: 0.15; clr: 192,192,192; }
cylinder { pnt: -1,-1,6; dir: -1,-2,6; rds: 0.15; clr: 192,192,192; }
cylinder { pnt: 1,1,1; dir: 1,2,1; rds: 0.15; clr: 192,192,192; }
cylinder { pnt: 1,-1,6; dir: 1,-2,6; rds: 0.15; clr: 192,192,192; }

cone { pnt: 2,0.5,4; dir: 2,1,4; alp: 20; clr: 0,255,0; } 
cone { pnt: -2,0.5,4; dir: -2,1,4; alp: 20; clr: 0,255,0; } 

light { pnt: -2,0,-4; int: 0.3; }
light { pnt: 2,0,-4; int: 0.3; }

camera { dir: 0,0,0; pnt: 0,0,-6; }
