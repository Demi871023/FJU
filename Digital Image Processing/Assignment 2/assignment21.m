% 載入實驗圖片
Image = imread('headCT.tif');
[Gmag, Gdir] = imgradient(Image,'prewitt');
%figure, imshow(Iblur);