import open3d as o3d
import copy

def draw_registration_result_original_color(source,target, transformation):
	source_temp = copy.deepcopy(source)
	target_temp=copy.deepcopy(target)
	source_temp.transform(transformation)

	o3d.visualization.draw_geometries([source_temp, target_temp])

def color_ICP(source,target,T):
	voxel_radius = [0.16, 0.08, 0.04, 0.02]
	max_iter = [5000, 2500, 1250, 625]

	current_transformation = T

	for scale in range(len(voxel_radius)):
		iter = max_iter[scale]
		radius = voxel_radius[scale]

		source_down=copy.deepcopy(source)
		target_down=copy.deepcopy(target)
		source_down.estimate_normals(
			o3d.geometry.KDTreeSearchParamHybrid(radius=radius*2, max_nn=30))
		target_down.estimate_normals(
			o3d.geometry.KDTreeSearchParamHybrid(radius=radius*2, max_nn=30))

		result_icp = o3d.pipelines.registration.registration_colored_icp(
			source_down, target_down, radius, current_transformation,
			o3d.pipelines.registration.TransformationEstimationForColoredICP(),
			o3d.pipelines.registration.ICPConvergenceCriteria(relative_fitness=1e-6,
															  relative_rmse=1e-6,
															  max_iteration=iter))#6
		current_transformation = result_icp.transformation
		print(current_transformation)
		print(result_icp)
	draw_registration_result_original_color(source, target,
											result_icp.transformation)
	return result_icp.transformation