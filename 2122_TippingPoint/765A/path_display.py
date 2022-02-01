import PIL 
from PIL import Image, ImageDraw
import matplotlib
import re 
import math
# function = input("Enter function name: ")

functiontext = ""

with open("src/main.cpp", "r+") as texthandle:
    file = ""
    for line in texthandle:
        file += line
    # searchstring = "void " + function + "(.*)\}void"
    searchstring = "void leftskills"
    match = file.index("leftskills")
    match2 = file.index("void rightrings")
    function = file[match + 15:match2-4]
    function = function.replace(" ", "")
    # function = function.replace("\n", "")
    # print(function)
    commands = function.split("\n")
    movements = []
    for command in commands:
        command = command.strip()
        if command.startswith("distanceMove") or command.startswith("dragTurn") or command.startswith("goal.theta"):
            movements.append(command)
    # for movement in movements:
        # print(movement)
    
    #635 width for 12 ft
    #52.9 px / ft and 4.4 px / inch
    #starting position = (85, 85)
    base_image = Image.open("skills_field.PNG")
    drawing = ImageDraw.Draw(base_image)
    drawing.ellipse([(70,70),(100,100)], "black", "black")
    currentheading = 0
    currentmovement = 1
    oldx = 85
    oldy = 85
    n = 1
    for movement in movements:
        if movement.startswith("distanceMove"):
            arguments = movement[movement.index("(")+1:movement.index(")")].replace(" ", "").split(",")
            # arguments = arguments.replace(" ", "")
            # arguments = arguments.split(",")
            # print(arguments)
            distance = int(arguments[0])
            direction = float(arguments[1])
            if direction < 0:
                currentmovement = -1
                newx = oldx + (distance * 4.4 * math.cos(math.pi / 2 + ((90-currentheading) * math.pi / 180)))
                newy = oldy + (distance * 4.4 * math.sin(math.pi / 2 + ((90-currentheading) * math.pi / 180)))  
            else:
                currentmovement = 1
                newx = oldx + (distance * 4.4 * math.cos((90-currentheading) * math.pi / 180))
                newy = oldy + (distance * 4.4 * math.sin((90-currentheading) * math.pi / 180))
            
            drawing.line([(oldx, oldy),(newx,newy)], "black", 2)
            oldx = newx
            oldy = newy
            # direction = int(arguments[1])

        if movement.startswith("goal.theta"):
            currentheading = int(movement[movement.index("=")+2:movement.index("_")].replace(" ", ""))
        n += 1
        if n > 2:
            break
    base_image.show()