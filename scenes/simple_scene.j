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
      "reflective" : 0,
      "texture" : "./textures/earth.png"
    },
    {
      "type" : "sphere",
      "origin" : [-2, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 0],
      "reflective" : 0,
      "texture" : "./textures/earth.png"
    },
    {
      "type" : "sphere",
      "origin" : [2, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 0],
      "reflective" : 0
    },
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [0, 5, 20]
    }
  ]
}

