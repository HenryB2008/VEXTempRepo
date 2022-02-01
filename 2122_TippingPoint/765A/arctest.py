import PIL
from PIL import Image, ImageDraw


base_image = Image.open("skills_field.PNG")
drawing = ImageDraw.Draw(base_image)
drawing.arc([(500, 500),(600, 600)], 180, 285, "black")
base_image.show()