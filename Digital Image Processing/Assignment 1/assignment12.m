% 載入實驗圖片
Image = imread('Bear.jpg');

% 將原始 RGB 圖片轉為 Gray Scale 圖片
grayImage = rgb2gray(Image);

% 將圖片縮小 2 倍，一共 6 次。再將圖片放大 128 倍回原始圖片大小
ResizeImage_nearest5 = imresize(grayImage, 0.0078125, 'nearest');
EnlargeImage_nearest5 = imresize(ResizeImage_nearest5, 128, 'nearest');
ResizeImage_bilinear5 = imresize(grayImage, 0.0078125, 'bilinear');
EnlargeImage_bilinear5 = imresize(ResizeImage_bilinear5, 128, 'bilinear');
ResizeImage_bicubic5 = imresize(grayImage, 0.0078125, 'bicubic');
EnlargeImage_bicubic5 = imresize(ResizeImage_bicubic5, 128, 'bicubic');

% 輸出原始圖片、使用 3 種方法的縮小圖及放大圖，共 7 張
    % 原始圖片
figure, imshow(grayImage), title('Origin Image');
    % Nearst Method
figure, subplot(1,2,1), imshow(ResizeImage_nearest5), title('Nearest Image 0.0078125');
subplot(1,2,2), imshow(EnlargeImage_nearest5), title('Recover Nearest Image 128');
    % Bilinear Method
figure, subplot(1,2,1), imshow(ResizeImage_bilinear5), title('Bilinear Image 0.0078125');
subplot(1,2,2), imshow(EnlargeImage_bilinear5), title('Recover Bilinear Image 128');
    % Bicubic Method
figure, subplot(1,2,1), imshow(ResizeImage_bicubic5), title('Bicubic Image 0.0078125');
subplot(1,2,2), imshow(EnlargeImage_bicubic5), title('Recover Bicubic Image 128');