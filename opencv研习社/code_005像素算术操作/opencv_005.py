import cv2 as cv
import numpy as np

src1 = cv.imread("C:\\Users\\admin\\Documents\\Visual Studio 2015\\Projects\\Testphoto\\LinuxLogo.jpg");
src2 = cv.imread("C:\\Users\\admin\\Documents\\Visual Studio 2015\\Projects\\Testphoto\\WindowsLogo.jpg");
cv.imshow("input1", src1)
cv.imshow("input2", src2)
h, w, ch = src1.shape
print("h , w, ch", h, w, ch)

add_result = np.zeros(src1.shape, src1.dtype);
cv.add(src1, src2, add_result);
cv.imshow("add_result", add_result);

sub_result = np.zeros(src1.shape, src1.dtype);
cv.subtract(src1, src2, sub_result);
cv.imshow("sub_result", sub_result);

mul_result = np.zeros(src1.shape, src1.dtype);
cv.multiply(src1, src2, mul_result);
cv.imshow("mul_result", mul_result);

div_result = np.zeros(src1.shape, src1.dtype);
cv.divide(src1, src2, div_result);
cv.imshow("div_result", div_result);

cv.waitKey(0)
cv.destroyAllWindows()

