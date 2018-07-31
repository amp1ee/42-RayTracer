{
  "camera" : [
    {
      "origin" : [0,0,-18],
      "direction" : [0, 0, 1]
    }
  ],

  "objects" : [

    {
      "type" : "ellipsoid",
      "origin" : [-7, 0, 20],
      "direction" : [0, 1, 0],
      "radius": 2.0,
      "color" : [0, 255, 255],
      "reflective" : 0
    },
    {
      "type" : "ellipsoid",
      "origin" : [0, 0, 20],
      "direction" : [0, 1, 0],
      "radius": 2.0,
      "color" : [0, 255, 255],
      "reflective" : 0.5
    },
    {
      "type" : "ellipsoid",
      "origin" : [7, 0, 20],
      "direction" : [0, 1, 0],
      "radius": 2.0,
      "color" : [0, 255, 255],
      "reflective" : 1
    },
    {
      "type" : "paraboloid",
      "origin" : [20, 12, 15],
      "cap" : 20.0,
      "direction" : [0, 1, 0],
      "color" : [255, 0, 0]
    },
    {
      "type" : "plane",
      "origin" : [0, -2, 20],
      "direction" : [0, 1, 0],
      "color" : [255, 255, 255]
    }
    {
      "type" : "plane",
      "origin" : [0, 40, 20],
      "direction" : [0, -1, 0],
      "color" : [255, 255, 255]
    }
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 1,
      "position" : [0, 0, 0]
    },

  ]
}
