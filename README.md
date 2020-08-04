# trajectory_evaluation
A package to be used with rpg_trajectory_evaluation
- https://github.com/uzh-rpg/rpg_trajectory_evaluation#evaluation-parameters

#### Usage
- A node that subscribes to the  ```grountruth_topic``` and ```trajectory_estimation``` topic and writes them to a file in the prescribed format
```
rosrun traj_eval vm_eval
```

#### Poses
The groundtruth (`stamped_groundtruth.txt`) and estimated poses (`stamped_traj_estimate.txt`) are specified in the following format

```
# timestamp tx ty tz qx qy qz qw
1.403636580013555527e+09 1.258278699999999979e-02 -1.561510199999999963e-03 -4.015300900000000339e-02 -5.131151899999999988e-02 -8.092916900000000080e-01 8.562779200000000248e-04 5.851609599999999523e-01
......
```
