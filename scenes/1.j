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
      "origin" : [-2, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 0],
      "texture" : "./textures/wall.jpg"
    },
    {
      "type" : "sphere",
      "origin" : [0, 0, 20],
      "radius" : 1,
      "color" : [0, 0, 255],
      "texture" : "./textures/pustynia.jpg"
    },
    {
      "type" : "sphere",
      "origin" : [2, 0, 20],
      "radius" : 1,
      "color" : [255, 255, 0],
      "texture" : "./textures/earth.png"
    }
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [0, 5, 20]
    },
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [-2, 5, 20]
    },
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [-2, -5, 20]
    },
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [-2, 0, -20]
    }
  ]
}
