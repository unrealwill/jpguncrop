# jpguncrop
jpg Acropalypse POC

Suppose you have two identical images except for one circle being blue and the other being red, and then you compress them with jpg.

![redcircle.jpg](redcircle.jpg?raw=true)
![bluecircle.jpg](bluecircle.jpg?raw=true)

If you redact these jpg files now and save them losslessly

![croppedred.png](croppedred.png?raw=true)
![croppedblue.png](croppedblue.png?raw=true)

In fact due to jpg compression artifact the files are different and therefore you can unredact them.

Diff between the two images :

![Pixel wise diff](diff.png?raw=true)

See jpguncrop.cpp for how the images are constructed.

require opencv and build with :
> cmake .

> make
