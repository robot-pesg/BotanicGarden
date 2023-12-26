# State-Of-The-Art Evaluation
We have tested the performance of visual ([ORB-SLAM3](https://github.com/UZ-SLAMLab/ORB_SLAM3)), visual-inertial ([ORB-SLAM3](https://github.com/UZ-SLAMLab/ORB_SLAM3), [VINS-Mono](https://github.com/HKUST-Aerial-Robotics/VINS-Mono)), LiDAR ([LOAM](https://github.com/HKUST-Aerial-Robotics/A-LOAM)), LiDAR-inertial ([Fast-LIO2](https://github.com/hku-mars/FAST_LIO)), and visual-LiDAR-inertial fusion ([LVI-SAM](https://github.com/TixiaoShan/LVI-SAM), [R3LIVE](https://github.com/hku-mars/r3live)) systems on the above 7 sample sequences, as listed below the evaluation statistics.

<table>
    <tr> <!-- 第1行数据 -->
        <td style="text-align:center"> Sequence </td>  <!-- 第1列 -->
        <td style="text-align:center" colspan="2"> 1005-00 </td> <!-- 第2列 合并了 2 列 -->
        <td style="text-align:center" colspan="2"> 1005-01 </td> <!-- 第4列 合并了 2 列 -->
        <td style="text-align:center" colspan="2"> 1005-07 </td> <!-- 第6列 合并了 2 列 -->
        <td style="text-align:center" colspan="2"> 1006-01 </td> <!-- 第8列 合并了 2 列 -->
        <td style="text-align:center" colspan="2"> 1008-03 </td> <!-- 第10列 合并了 2 列 -->
        <td style="text-align:center" colspan="2"> 1018-00 </td> <!-- 第12列 合并了 2 列 -->
        <td style="text-align:center" colspan="2"> 1018-13 </td> <!-- 第14列 合并了 2 列 -->
    </tr>
    <tr> <!-- 第2行数据 -->
        <td style="text-align:center"> Method/Metric </td>  <!-- 第1列 -->
        <td style="text-align:center"> RPE/% </td>  <!-- 第2列 -->
        <td style="text-align:center"> ATE/m </td>  <!-- 第3列 -->
        <td style="text-align:center"> RPE/% </td>  <!-- 第4列 -->
        <td style="text-align:center"> ATE/m </td>  <!-- 第5列 -->
        <td style="text-align:center"> RPE/% </td>  <!-- 第6列 -->
        <td style="text-align:center"> ATE/m </td>  <!-- 第7列 -->
        <td style="text-align:center"> RPE/% </td>  <!-- 第8列 -->
        <td style="text-align:center"> ATE/m </td>  <!-- 第9列 -->
        <td style="text-align:center"> RPE/% </td>  <!-- 第10列 -->
        <td style="text-align:center"> ATE/m </td>  <!-- 第11列 -->
        <td style="text-align:center"> RPE/% </td>  <!-- 第12列 -->
        <td style="text-align:center"> ATE/m </td>  <!-- 第13列 -->
        <td style="text-align:center"> RPE/% </td>  <!-- 第14列 -->
        <td style="text-align:center"> ATE/m </td>  <!-- 第15列 -->
    </tr>
    <tr> <!-- 第3行数据 -->
        <td style="text-align:center"> ORB-SLAM3-S </td>  <!-- 第1列 -->
        <td style="text-align:center"> X </td>  <!-- 第2列 -->
        <td style="text-align:center"> X </td>  <!-- 第3列 -->
        <td style="text-align:center"> 5.586 NC </td>  <!-- 第4列 -->
        <td style="text-align:center"> 5.933 NC</td>  <!-- 第5列 -->
        <td style="text-align:center"> X </td>  <!-- 第6列 -->
        <td style="text-align:center"> X </td>  <!-- 第7列 -->
        <td style="text-align:center"> 4.143 LC </td>  <!-- 第8列 -->
        <td style="text-align:center"> 3.453 LC </td>  <!-- 第9列 -->
        <td style="text-align:center"> 4.148 LC </td>  <!-- 第10列 -->
        <td style="text-align:center"> 5.005 LC </td>  <!-- 第11列 -->
        <td style="text-align:center"> 5.220 NC </td>  <!-- 第12列 -->
        <td style="text-align:center"> 1.466 NC </td>  <!-- 第13列 -->
        <td style="text-align:center"> 5.303 NC </td>  <!-- 第14列 -->
        <td style="text-align:center"> 2.818 NC </td>  <!-- 第15列 -->
    </tr>
    <tr> <!-- 第4行数据 -->
        <td style="text-align:center"> ORB-SLAM3-SI </td>  <!-- 第1列 -->
        <td style="text-align:center"> 4.386 NC </td>  <!-- 第2列 -->
        <td style="text-align:center"> 5.511 NC </td>  <!-- 第3列 -->
        <td style="text-align:center"> 4.808 NC </td>  <!-- 第4列 -->
        <td style="text-align:center"> 5.376 NC </td>  <!-- 第5列 -->
        <td style="text-align:center"> 4.771 NC </td>  <!-- 第6列 -->
        <td style="text-align:center"> 5.283 NC </td>  <!-- 第7列 -->
        <td style="text-align:center"> 3.733 LC </td>  <!-- 第8列 -->
        <td style="text-align:center"> 3.150 LC </td>  <!-- 第9列 -->
        <td style="text-align:center"> 3.853 LC </td>  <!-- 第10列 -->
        <td style="text-align:center"> 4.311 LC </td>  <!-- 第11列 -->
        <td style="text-align:center"> 4.118 LC </td>  <!-- 第12列 -->
        <td style="text-align:center"> 1.116 LC </td>  <!-- 第13列 -->
        <td style="text-align:center"> 4.238 NC </td>  <!-- 第14列 -->
        <td style="text-align:center"> 2.967 NC </td>  <!-- 第15列 -->
    </tr>
    <tr> <!-- 第5行数据 -->
        <td style="text-align:center"> VINS-Mono </td>  <!-- 第1列 -->
        <td style="text-align:center"> 3.403 NC </td>  <!-- 第2列 -->
        <td style="text-align:center"> 8.617 NC </td>  <!-- 第3列 -->
        <td style="text-align:center"> 2.383 NC </td>  <!-- 第4列 -->
        <td style="text-align:center"> 4.029 NC </td>  <!-- 第5列 -->
        <td style="text-align:center"> 3.694 NC </td>  <!-- 第6列 -->
        <td style="text-align:center"> 7.819 NC </td>  <!-- 第7列 -->
        <td style="text-align:center"> 3.101 LC </td>  <!-- 第8列 -->
        <td style="text-align:center"> 2.318 LC </td>  <!-- 第9列 -->
        <td style="text-align:center"> 3.475 LC </td>  <!-- 第10列 -->
        <td style="text-align:center"> 3.620 LC </td>  <!-- 第11列 -->
        <td style="text-align:center"> 3.859 NC </td>  <!-- 第12列 -->
        <td style="text-align:center"> 1.767 NC </td>  <!-- 第13列 -->
        <td style="text-align:center"> 5.588 NC </td>  <!-- 第14列 -->
        <td style="text-align:center"> 2.967 NC </td>  <!-- 第15列 -->
    </tr>
    <tr> <!-- 第6行数据 -->
        <td style="text-align:center"> LOAM </td>  <!-- 第1列 -->
        <td style="text-align:center"> 1.993 </td>  <!-- 第2列 -->
        <td style="text-align:center"> 3.744 </td>  <!-- 第3列 -->
        <td style="text-align:center"> 2.589 </td>  <!-- 第4列 -->
        <td style="text-align:center"> 5.624 </td>  <!-- 第5列 -->
        <td style="text-align:center"> 2.293 </td>  <!-- 第6列 -->
        <td style="text-align:center"> 3.253 </td>  <!-- 第7列 -->
        <td style="text-align:center"> 2.188 </td>  <!-- 第8列 -->
        <td style="text-align:center"> 2.553 </td>  <!-- 第9列 -->
        <td style="text-align:center"> 2.046 </td>  <!-- 第10列 -->
        <td style="text-align:center"> 2.994 </td>  <!-- 第11列 -->
        <td style="text-align:center"> 2.530 </td>  <!-- 第12列 -->
        <td style="text-align:center"> 0.523 </td>  <!-- 第13列 -->
        <td style="text-align:center"> 2.441 </td>  <!-- 第14列 -->
        <td style="text-align:center"> 1.330 </td>  <!-- 第15列 -->
    </tr>
    <tr> <!-- 第7行数据 -->
        <td style="text-align:center"> FAST-LIO2 </td>  <!-- 第1列 -->
        <td style="text-align:center"> 1.827 </td>  <!-- 第2列 -->
        <td style="text-align:center"> 2.305 </td>  <!-- 第3列 -->
        <td style="text-align:center"> 1.870 </td>  <!-- 第4列 -->
        <td style="text-align:center"> 2.470 </td>  <!-- 第5列 -->
        <td style="text-align:center"> 2.349 </td>  <!-- 第6列 -->
        <td style="text-align:center"> 4.438 </td>  <!-- 第7列 -->
        <td style="text-align:center"> 6.573 </td>  <!-- 第8列 -->
        <td style="text-align:center"> 39.733 </td>  <!-- 第9列 -->
        <td style="text-align:center"> 2.404 </td>  <!-- 第10列 -->
        <td style="text-align:center"> 4.019 </td>  <!-- 第11列 -->
        <td style="text-align:center"> 2.770 </td>  <!-- 第12列 -->
        <td style="text-align:center"> 2.154 </td>  <!-- 第13列 -->
        <td style="text-align:center"> 2.562 </td>  <!-- 第14列 -->
        <td style="text-align:center"> 2.390 </td>  <!-- 第15列 -->
    </tr>
    <tr> <!-- 第8行数据 -->
        <td style="text-align:center"> LVI-SAM </td>  <!-- 第1列 -->
        <td style="text-align:center"> 1.899 </td>  <!-- 第2列 -->
        <td style="text-align:center"> 2.774 </td>  <!-- 第3列 -->
        <td style="text-align:center"> 2.033 </td>  <!-- 第4列 -->
        <td style="text-align:center"> 2.640 </td>  <!-- 第5列 -->
        <td style="text-align:center"> 2.295 </td>  <!-- 第6列 -->
        <td style="text-align:center"> 3.232 </td>  <!-- 第7列 -->
        <td style="text-align:center"> 2.004 </td>  <!-- 第8列 -->
        <td style="text-align:center"> 1.700 </td>  <!-- 第9列 -->
        <td style="text-align:center"> 1.799 </td>  <!-- 第10列 -->
        <td style="text-align:center"> 1.798 </td>  <!-- 第11列 -->
        <td style="text-align:center"> 2.595 </td>  <!-- 第12列 -->
        <td style="text-align:center"> 0.700 </td>  <!-- 第13列 -->
        <td style="text-align:center"> 2.565 </td>  <!-- 第14列 -->
        <td style="text-align:center"> 1.061 </td>  <!-- 第15列 -->
    </tr>
    <tr> <!-- 第9行数据 -->
        <td style="text-align:center"> R3LIVE </td>  <!-- 第1列 -->
        <td style="text-align:center"> 1.924 </td>  <!-- 第2列 -->
        <td style="text-align:center"> 3.300 </td>  <!-- 第3列 -->
        <td style="text-align:center"> 1.907 </td>  <!-- 第4列 -->
        <td style="text-align:center"> 2.259 </td>  <!-- 第5列 -->
        <td style="text-align:center"> 2.197 </td>  <!-- 第6列 -->
        <td style="text-align:center"> 3.799 </td>  <!-- 第7列 -->
        <td style="text-align:center"> 2.192 </td>  <!-- 第8列 -->
        <td style="text-align:center"> 7.051 </td>  <!-- 第9列 -->
        <td style="text-align:center"> 2.077 </td>  <!-- 第10列 -->
        <td style="text-align:center"> 2.776 </td>  <!-- 第11列 -->
        <td style="text-align:center"> 2.462 </td>  <!-- 第12列 -->
        <td style="text-align:center"> 0.875 </td>  <!-- 第13列 -->
        <td style="text-align:center"> 2.779 </td>  <!-- 第14列 -->
        <td style="text-align:center"> 1.318 </td>  <!-- 第15列 -->
    </tr>
</table>