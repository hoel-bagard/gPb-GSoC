from pygpb import libgpb
import numpy as np
from skimage import io, color
import matplotlib.pyplot as plt
from skimage import io
import os 
import sys

if __name__ == "__main__":

    n_ori, Kmean_num, sigma_sm, sigma_lg = 8, 64, 2.0, np.sqrt(2)*2.0

    # get paths
    path = sys.argv[-1]
    res_path = os.path.split(path)[0]
    im_name = os.path.split(path)[1]
    gpb_name = '{}_gpb.png'.format(os.path.splitext(im_name)[0])
    gpb_path = os.path.join(res_path, gpb_name)
    ucm_name = '{}_ucm.png'.format(os.path.splitext(im_name)[0])
    ucm_path = os.path.join(res_path, ucm_name)

    # run it
    gpb = libgpb.Gpb()
    img = io.imread(path)
    if(img.strides[1] > 3):
        img = (255 * color.rgba2rgb(img)).astype(np.uint8)

    gpb.test_np_mat(img, img)

    # get texton
    texton = gpb.texton(img, n_ori,
                        Kmean_num,
                        sigma_sm, sigma_lg)
    gpb_res, ucm_res = gpb.run(img)

    # save images
    print('saving gPb to: {}'.format(gpb_path))
    io.imsave(gpb_path, gpb_res)
    print('saving UCM to: {}'.format(ucm_path))
    io.imsave(ucm_path, ucm_res / 255)

    # plot
    fig, ax = plt.subplots(1, 3)
    ax[0].imshow(gpb_res)
    ax[0].set_title('gPb')
    ax[1].imshow(ucm_res)
    ax[1].set_title('UCM')
    ax[2].imshow(texton)
    ax[2].set_title('texton')
    fig.show()

