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
      "type" : "2sheet_hyperboloid",
      "origin" : [-5, 2, 20],
      "radius": 1.0,
      "color" : [255, 255, 0]
    },
    {
      "type" : "paraboloid",
      "origin" : [10, 8, 20],
      "direction" : [0, -1, 0],
      "color" : [255, 0, 0]
    },
    {
      "type" : "plane",
      "origin" : [0, -2, 20],
      "direction" : [0, 1, 0],
      "color" : [255, 255, 255]
    }
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [0, 5, -10]
    },

    {
      "type" : "direct",
      "intensity" : 0.5,
      "direction" : [0, 1, 0]
    },

    {
      "type" : "ambient",
      "intensity" : 0.5
    }
  ]
}

