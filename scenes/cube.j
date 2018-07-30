{
  "camera" : [
    {
      "origin" : [0,0,0],
      "direction" : [0, 0, 0]
    }
  ],

  "objects" : [
    {
      "type" : "cube",
      "min" : [0, 0, 20],
      "max" : [1, 1, 21],
      "color" : [255, 0, 0]
    },
    {
      "type" : "cylinder",
      "origin" : [-2, 0, 20],
      "direction" : [-2, 1, 20],
      "size" : 10,
      "radius" : 1,
      "color" : [255, 0, 0],
      "texture" : "chessboard"
    },
    {
      "type" : "disk",
      "origin" : [2, 5, 20],
      "direction" : [0, 0.2, -1],
      "radius" : 1,
      "color" : [255, 0, 0]
    },
    {
      "type" : "plane",
      "origin" : [2, -2, 20],
      "direction" : [0, 1, -0.1],
      "color" : [255, 255, 0],
      "reflective" : 0
    },
    {
      "type" : "plane",
      "origin" : [2, -2, 20],
      "direction" : [0, -1, 0.1],
      "color" : [255, 0, 0],
      "reflective" : 0
    }
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [0, 1, 15]
    }
  ]
}

