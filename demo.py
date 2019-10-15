from pygpb import libgpb
import numpy as np
import matplotlib.pyplot as plt
import os 
import sys

if __name__ == "__main__":

    path = sys.argv[-1]
    res_path = os.path.split(path)[0]
    im_name = os.path.split(path)[1]
    gpb_name = '{}_gpb.png'.format(os.path.splitext(im_name)[0])
    gpb_path = os.path.join(res_path, gpb_name)
    ucm_name = '{}_ucm.png'.format(os.path.splitext(im_name)[0])
    ucm_path = os.path.join(res_path, ucm_name)
    img = plt.imread(path)

    test = np.random.randn(4,4,3)

    gpb = libgpb.Gpb()
    gpb_res, ucm_res = gpb.run(img)
    fig, ax = plt.subplots(1, 2)
    ax[0].imshow(gpb_res)
    ax[0].set_title('gPb')
    ax[1].imshow(ucm_res)
    ax[1].set_title('UCM')
    fig.show()

    print('saving gPb to: {}'.format(gpb_path))
    ax[0].imsave(gpb_res, gpb_path)
    print('saving UCM to: {}'.format(ucm_path))
    ax[1].imsave(ucm_res, ucm_path)
