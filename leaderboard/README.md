# Leaderborad

This benchmark is calculated by averaging the Relative Pose Error (RPE) of 7 sample sequences (short to long), including 1005-00, 1005-01, 1005-07, 1006-01, 1008-03, 1018-00, and 1018-13. RPE can make sense to serve as an invariant metric to trajectory length as it calculates error over fixed-length segments (100 meters) to avoid the impact of distance and accumulated errors.

<table>
    <!-- <tr>
        <th colspan="7">
            1005-00
        </th>
    </tr> -->
    <tr>
        <th>Rank</th>
        <th>Method</th>
        <th>Setting</th>
        <th>Code</th>
        <th>Relative Error</th>
        <!-- <th>ATE</th> -->
        <!-- <th>Runtime</th> -->
    </tr>
    <tr>
        <th>1</th>
        <th>LVI-SAM</th>
        <th>Visual-LiDAR-Inertial</th>
        <th><a href="https://github.com/TixiaoShan/LVI-SAM">Code</a></th>
        <th>2.170 %</th>
        <!-- <th>2.774 [m]</th> -->
        <!-- <th>--</th> -->
    </tr>
    <tr>
        <td colspan="5">
            <ul>
                <li>Shan T, Englot B, Ratti C, et al.: <i>Lvi-sam: Tightly-coupled lidar-visual-inertial odometry via smoothing and mapping.</i> IEEE International Conference on Robotics and Automation (ICRA) 2021.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <th>2</th>
        <th>R3LIVE</th>
        <th>Visual-LiDAR-Inertial</th>
        <th><a href="https://github.com/hku-mars/r3live">Code</a></th>
        <th>2.220 %</th>
        <!-- <th>3.300 [m]</th> -->
        <!-- <th>--</th> -->
    </tr>
    <tr>
        <td colspan="5">
            <ul>
                <li>Lin J, Zhang F.: <i>R3LIVE: A Robust, Real-time, RGB-colored, LiDAR-Inertial-Visual tightly-coupled state Estimation and mapping package.</i> IEEE International Conference on Robotics and Automation (ICRA) 2022.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <th>3</th>
        <th>LOAM</th>
        <th>Visual-LiDAR-Inertial</th>
        <th><a href="https://github.com/HKUST-Aerial-Robotics/A-LOAM">Code</a></th>
        <th>2.297 %</th>
        <!-- <th>3.744 [m]</th> -->
        <!-- <th>--</th> -->
    </tr>
    <tr>
        <td colspan="5">
            <ul>
                <li>Zhang J, Singh S.: <i>LOAM: Lidar odometry and mapping in real-time.</i> Robotics: Science and systems. (RSS) 2014.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <th>4</th>
        <th>Fast-LIO2</th>
        <th>LiDAR-Inertial</th>
        <th><a href="https://github.com/hku-mars/FAST_LIO">Code</a></th>
        <th>2.908 %</th>
        <!-- <th>2.305 [m]</th> -->
        <!-- <th>--</th> -->
    </tr>
    <tr>
        <td colspan="5">
            <ul>
                <li>Xu W, Cai Y, He D, et al.: <i>Fast-lio2: Fast direct lidar-inertial odometry.</i> IEEE Transactions on Robotics 2022.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <th>5</th>
        <th>VINS-Mono</th>
        <th>Visual-Inertial</th>
        <th><a href="https://github.com/HKUST-Aerial-Robotics/VINS-Mono">Code</a></th>
        <th>3.643 %</th>
        <!-- <th>8.617 [m]</th> -->
        <!-- <th>--</th> -->
    </tr>
    <tr>
        <td colspan="5">
            <ul>
                <li>Qin T, Li P, Shen S.: <i>Vins-mono: A robust and versatile monocular visual-inertial state estimator.</i> IEEE Transactions on Robotics. 2018.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <th>6</th>
        <th>ORB-SLAM3-SI</th>
        <th>Visual-Inertial</th>
        <th><a href="https://github.com/UZ-SLAMLab/ORB_SLAM3">Code</a></th>
        <th>4.272 %</th>
        <!-- <th>5.511 [m]</th> -->
        <!-- <th>--</th> -->
    </tr>
    <tr>
        <td colspan="5">
            <ul>
                <li>Campos C, Elvira R, Rodríguez J J G, et al.: <i>Orb-slam3: An accurate open-source library for visual, visual–inertial, and multimap slam.</i> IEEE Transactions on Robotics. 2021.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <th>7</th>
        <th>ORB-SLAM3-S</th>
        <th>Visual-Only</th>
        <th><a href="https://github.com/UZ-SLAMLab/ORB_SLAM3">Code</a></th>
        <th>4.880 %</th>
        <!-- <th>5.511 [m]</th> -->
        <!-- <th>--</th> -->
    </tr>
    <tr>
        <td colspan="5">
            <ul>
                <li>Campos C, Elvira R, Rodríguez J J G, et al.: <i>Orb-slam3: An accurate open-source library for visual, visual–inertial, and multimap slam.</i> IEEE Transactions on Robotics. 2021.</li>
            </ul>
        </td>
    </tr>
</table>