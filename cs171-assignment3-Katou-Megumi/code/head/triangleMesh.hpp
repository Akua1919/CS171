#pragma once
#include <vector>
#include "shape.hpp"
#include "objloader.hpp"
#include "refine.hpp"
#include <math.h>

class TriangleMesh : public Shape
{
public:
	// number of triangles
	int triangleCount;
	// verteces, normals and indices data
	std::vector<Eigen::Vector3f> out_vertices;
	std::vector<Eigen::Vector3f> out_normals;
	std::vector<int> out_v_index;
	std::vector<int> out_vn_index;
	// uniform grid data
	bool isUniformExisting;
	std::vector<std::vector<int>> grid;
	Eigen::Vector3i gridDim;
	Eigen::Vector3f gridDeltaDist;
	float unit;

	explicit TriangleMesh(const Eigen::Vector3f& color, std::string filePos)
		: Shape(color)
	{
		std::vector <Eigen::Vector2f> out_uvs;
		std::vector <int> out_vt_index;
		loadOBJ_index(filePos.c_str(), out_vertices, out_uvs, out_normals, out_v_index, out_vt_index, out_vn_index);
		
		triangleCount = out_v_index.size() / 3;
		
		m_BoundingBox.lb = out_vertices[0].cwiseMin(out_vertices[1]);
		m_BoundingBox.ub = out_vertices[0].cwiseMax(out_vertices[1]);
		for (int i = 2; i < out_vertices.size(); i++)
		{
			m_BoundingBox.lb = m_BoundingBox.lb.cwiseMin(out_vertices[i]);
			m_BoundingBox.ub = m_BoundingBox.ub.cwiseMax(out_vertices[i]);
		}

		isUniformExisting = false;
	}

	// ray intersection with single triangle, result saves in @Interaction
	bool raySingleTriangleIntersection(Interaction& interaction, const Ray& ray, int v0_idx, int v1_idx, int v2_idx)
	{
		Eigen::Vector3f A = out_vertices[out_v_index[v0_idx]];
		Eigen::Vector3f B = out_vertices[out_v_index[v1_idx]];
		Eigen::Vector3f C = out_vertices[out_v_index[v2_idx]];

		Eigen::Vector3f An = out_normals[out_vn_index[v0_idx]];
		Eigen::Vector3f Bn = out_normals[out_vn_index[v1_idx]];
		Eigen::Vector3f Cn = out_normals[out_vn_index[v2_idx]];

		Eigen::Vector3f P = ray.m_Ori;

		Eigen::Vector3f n = (B - A).cross(C - A);
		float d = -ray.m_Dir.dot(n);
		Eigen::Vector3f e =-ray.m_Dir.cross(P - A);

		if (d == 0.0f) {
			return false;
		}

		float t = (P - A).dot(n) / d;
		float v = (C - A).dot(e) / d;
		float w = -(B - A).dot(e) / d;
		
		if (ray.m_fMin <= t <= ray.m_fMax && v>=0 && w>=0 && v+w<=1) {
			interaction.entryDist = t;
			interaction.entryPoint = ray.getPoint(t);
			interaction.normal = ((1-v-w)* An + v* Bn + w * Cn).normalized();
			interaction.uv = Eigen::Vector2f(v, w);
			interaction.surfaceColor = color;
			return true;
		}
		return false;
	}
	
	// ray intersection with mesh, result saves in @Interaction
	bool rayIntersection(Interaction& interaction, const Ray& ray) override
	{
		Interaction finalInteraction;
		if (isUniformExisting) {
			Eigen::Vector3f entry_point = ray.getPoint(interaction.entryDist) - m_BoundingBox.lb;
			Eigen::Vector3i grid_cell = (entry_point * unit).cast<int>();

			int stepX,stepY,stepZ;
			float tMaxX,tMaxY,tMaxZ;
			float tDeltaX,tDeltaY,tDeltaZ;

			if (ray.m_Dir.x() > 0) {
				stepX = 1;
			}
			else {
				stepX = -1;
			}
			if (ray.m_Dir.y() > 0) {
				stepY = 1;
			}
			else {
				stepY = -1;
			}
			if (ray.m_Dir.z() > 0) {
				stepZ = 1;
			}
			else {
				stepZ = -1;
			}

			tMaxX = ((grid_cell[0] + (ray.m_Dir[0]>0)) / unit - entry_point[0]) / ray.m_Dir[0];
			tMaxY = ((grid_cell[1] + (ray.m_Dir[1]>0)) / unit - entry_point[1]) / ray.m_Dir[1];
			tMaxZ = ((grid_cell[2] + (ray.m_Dir[2]>0)) / unit - entry_point[2]) / ray.m_Dir[2];
			tDeltaX = (1/(unit * ray.m_Dir[0])) * stepX;
			tDeltaY = (1/(unit * ray.m_Dir[1])) * stepY;
			tDeltaZ = (1/(unit * ray.m_Dir[2])) * stepZ;

			int idx = grid_cell.x() * gridDim.y() * gridDim.z() + grid_cell.y() * gridDim.z() + grid_cell.z();
			std::vector<int>* cell = &grid[idx];
			
			while (true) {
				if (cell && cell->size() > 0) {
					for (int i = 0; i < cell->size(); i++) {
						Interaction curInteraction;
						int index = grid[idx][i];
						if (raySingleTriangleIntersection(curInteraction, ray, 3 * index, 3 * index + 1, 3 * index + 2)) {
							if (finalInteraction.entryDist == -1 || (curInteraction.entryDist < finalInteraction.entryDist)) {
								finalInteraction = curInteraction;
							}
						}
					}
					if (finalInteraction.entryDist != -1) {
						break;
					}
				}

				int k;

				if (tMaxX<tMaxY)
				{
					if (tMaxX<tMaxZ)
					{
						k = 0;
					}
					else
					{
						k = 2;
					}
				}
				else
				{
					if (tMaxY<tMaxZ)
					{
						k = 1;
					}
					else
					{
						k = 2;
					}
				}

				switch (k)
				{
				case 0:
					tMaxX += tDeltaX;
					grid_cell[k] += stepX;
					break;
				case 1:
					tMaxY += tDeltaY;
					grid_cell[k] += stepY;
					break;
				case 2:
					tMaxZ += tDeltaZ;
					grid_cell[k] += stepZ;
					break;
				default:
					break;
				}

				if (grid_cell[k] < 0 || grid_cell[k] >= gridDim[k]) {
					break;
				}

				idx = grid_cell.x() * gridDim.y() * gridDim.z() + grid_cell.y() * gridDim.z() + grid_cell.z();
				cell = &grid[idx];
			}
		} else {
			for (int i = 0; i < triangleCount; i++) {
				Interaction curInteraction;
				if (raySingleTriangleIntersection(curInteraction, ray, 3 * i, 3 * i + 1, 3 * i + 2)) {
					if (finalInteraction.entryDist == -1 || curInteraction.entryDist < finalInteraction.entryDist) {
						finalInteraction = curInteraction;
					}
				}
			}
		}

		if (finalInteraction.entryDist != -1)
		{
			interaction = finalInteraction;
			return true;
		}
		return false;
	}

	// apply a certain transformation to all vertices, normals and bounding box
	void applyTransformation(const Eigen::Affine3f& t)
	{
		for (int i = 0; i < out_vertices.size(); i++)
		{
			out_vertices[i] = t * out_vertices[i];
		}

		Eigen::Matrix3f tInvTr = t.linear().inverse().transpose();
		for (int i = 0; i < out_normals.size(); i++)
		{
			out_normals[i] = (tInvTr * out_normals[i]).normalized();
		}

		m_BoundingBox.lb = out_vertices[0].cwiseMin(out_vertices[1]);
		m_BoundingBox.ub = out_vertices[0].cwiseMax(out_vertices[1]);
		for (int i = 2; i < out_vertices.size(); i++)
		{
			m_BoundingBox.lb = m_BoundingBox.lb.cwiseMin(out_vertices[i]);
			m_BoundingBox.ub = m_BoundingBox.ub.cwiseMax(out_vertices[i]);
		}
	}

	void subdivision(int division_time)
	{
		std::vector<ref::point> P_list(out_vertices.size());
		std::vector<ref::line> L_list;
		std::vector<ref::face> F_list(int(out_v_index.size() / 3));
		std::map<std::pair<int, int>, int> dic;
		std::vector<ref::point> P_list_new;
		std::vector<ref::line> L_list_new;
		std::vector<ref::face> F_list_new;
		std::map<std::pair<int, int>, int> dic_new;

		ref::build_data_struct(out_vertices, out_normals,out_v_index, out_vn_index,P_list, L_list, F_list, dic);

		for (int i = 0; i < division_time; i++) {
			ref::loop_subdivision(P_list, L_list, F_list,P_list_new, L_list_new, F_list_new, dic, dic_new);
			P_list.swap(P_list_new);
			L_list.swap(L_list_new);
			F_list.swap(F_list_new);
			dic.swap(dic_new);
			P_list_new.clear();
			L_list_new.clear();
			F_list_new.clear();
			dic_new.clear();
		}

		out_vertices.clear();
		out_normals.clear();
		out_v_index.clear();
		out_vn_index.clear();
		for (int i = 0; i < P_list.size(); i++) {
			out_vertices.push_back(P_list[i].pos);
			out_normals.push_back(P_list[i].normal);
		}
		for (int i = 0; i < F_list.size(); i++) {
			out_v_index.push_back(F_list[i].v[0]);
			out_v_index.push_back(F_list[i].v[1]);
			out_v_index.push_back(F_list[i].v[2]);
			out_vn_index.push_back(F_list[i].v[0]);
			out_vn_index.push_back(F_list[i].v[1]);
			out_vn_index.push_back(F_list[i].v[2]);
		}

		// Finally, update the new size
		triangleCount = out_v_index.size() / 3;
	}

	void buildUniformGrid() {
		int lambda = 4;
		float dx = m_BoundingBox.getDist(0);
		float dy = m_BoundingBox.getDist(1);
		float dz = m_BoundingBox.getDist(2);
		float V = m_BoundingBox.getVolume();
		unit = std::cbrtf((lambda * triangleCount)/V);
		gridDeltaDist  = Eigen::Vector3f( dx, dy, dz);
		gridDim = Eigen::Vector3i ( ceil(dx * unit), ceil(dy  * unit), ceil(dz * unit));

		grid = std::vector<std::vector<int>>(gridDim[0] * gridDim[1] * gridDim[2], std::vector<int>());

		for (int i = 0; i < triangleCount; i++) {
			Eigen::Vector3f A = out_vertices[out_v_index[3 * i]];
			Eigen::Vector3f B = out_vertices[out_v_index[3 * i + 1]];
			Eigen::Vector3f C = out_vertices[out_v_index[3 * i + 2]];

			int xmin, xmax, ymin, ymax, zmin, zmax;

			xmin = (min(min(A.x(), B.x()), C.x()) - m_BoundingBox.lb.x()) * unit;
			xmax = (max(max(A.x(), B.x()), C.x()) - m_BoundingBox.lb.x()) * unit;
			ymin = (min(min(A.y(), B.y()), C.y()) - m_BoundingBox.lb.y()) * unit;
			ymax = (max(max(A.y(), B.y()), C.y()) - m_BoundingBox.lb.y())* unit;
			zmin = (min(min(A.z(), B.z()), C.z()) - m_BoundingBox.lb.z()) * unit;
			zmax = (max(max(A.z(), B.z()), C.z()) - m_BoundingBox.lb.z()) * unit;

			for (int x = xmin; x <= xmax; x++) {
				for (int y = ymin; y <=ymax; y++) {
					for (int z =zmin; z <= zmax; z++) {
						int idx = x * gridDim.y() * gridDim.z() + y * gridDim.z() + z;
						grid[idx].push_back(i);
					}
				}
			}
		}

		// Don't forget to change isUniformExisting to true after building the grid
		isUniformExisting = true;
	}

};