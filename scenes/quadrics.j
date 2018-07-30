{
  "camera" : [
    {
      "origin" : [0,0,0],
      "direction" : [0, 0, 0]
    }
  ],

  "objects" : [
    {
      "type" : "sphere",
      "origin" : [0, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 0],
      "reflective" : 1
    },
    {
      "type" : "hyperboloid",
      "origin" : [-5, 2, 20],
      "radius": 2.0,
      "color" : [255, 255, 0]
    },
    {
      "type" : "2sheet_hyperboloid",
      "origin" : [-15, 2, 10],
      "radius": 1.0,
      "color" : [255, 0, 255]
    },
    {
      "type" : "ellipsoid",
      "origin" : [5, 2, 20],
      "direction" : [1, 0, 1],
      "radius": 2.0,
      "color" : [0, 255, 255]
    },
    {
      "type" : "paraboloid",
      "origin" : [10, 2, 15],
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
      "origin" : [0, -15, 20],
      "direction" : [0, -1, 0],
      "color" : [255, 255, 255]
    }
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [5, 2, -10]
    },
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [-5, 2, -10]
    }
  ]
}

