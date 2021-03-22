#pragma once
#include <vector>
//#include "../3rdLibs/glm/glm/glm.hpp"
#include "Eigen/Dense"
#include <algorithm>
#include <map>
#define pi 3.1415926
//////////////////////////////////////////////////////////////////////////////////////////////
// You should try to reduce the time complexity. For each time of loop subdivision (divide  //
// once), the time complexity of your program should not be lower than O(p^2+f*l) (p:number //
// of points, f: number of faces, l: number of lines). And try to explain how you reduce the//
// time complexity in you report and video.                                                 //
//                                                                                          //
// The following is a reference for you to do loop subdivision.                             //
//////////////////////////////////////////////////////////////////////////////////////////////
namespace ref {
	class point {
	public:
		Eigen::Vector3f pos;
        Eigen::Vector2f uv;	// you can ignore uv
        Eigen::Vector3f normal;	
        //one pos may have different, if you want to use exact value, you should store this
        //std::vector<Eigen::Vector2f> uv;
        //std::vector<Eigen::Vector3f> normal;
        std::vector<int> n_face;
        std::vector<int> n_point;
        std::vector<int> b_point;
        std::vector<int> n_line;
        bool is_border;
        point();
        ~point();
	};

	class face {
    public:
        int v[3];   //We have to use index, instead of point itself;
        //std::vector<Eigen::Vector2f> n_line;
        std::vector<int> n_line;
	};

	class line {
    public:
        int v1;     //We have to use index, instead of point itself;
        int v2;
        std::vector<int> n_face;
        bool is_border;
        bool new_point;
        int new_point_index;
        line();
        ~line();
	};
    
    // Decide whether a line is boundary: Find adj faces of one of the two points, and check whether any of them used the other point.
    // Use face as the iterator of loop to find lines
    
    void build_data_struct(
        std::vector < Eigen::Vector3f > out_vertices,
        std::vector < Eigen::Vector3f > out_normals,
        std::vector < int > out_v_index,
        std::vector < int > out_vn_index,
        std::vector<ref::point>& P_list,
        std::vector<ref::line>& L_list,
        std::vector<ref::face>& F_list,
        std::map<std::pair<int, int>, int>& dic);
    

    // Loop subdivision
    void loop_subdivision(
        std::vector<ref::point> P_list,
        std::vector<ref::line> L_list,
        std::vector<ref::face> F_list,
        std::vector<ref::point>& P_list_new,
        std::vector<ref::line>& L_list_new,
        std::vector<ref::face>& F_list_new,
        std::map<std::pair<int, int>, int>& dic,
        std::map<std::pair<int, int>, int>& dic_new);

    void make_face(
        std::vector<ref::point> P_list,
        std::vector<ref::face> F_list,
        std::vector<Eigen::Vector3f>& points, 
        std::vector<Eigen::Vector3f>& normals, 
        std::vector<Eigen::Vector2f>& uvs
    );
}
//line will decide which point is boundary
ref::point::point()
{
    this->is_border = false;
}
ref::point::~point()
{
    
}
//face will decide which line is not boundary
ref::line::line()
{
    this->is_border = true;
    this->new_point = false;
}
ref::line::~line()
{
    
}

std::pair<int, int> line_point(int x, int y) {
    if (x < y) {
        return std::make_pair(x, y);
    }
    else {
        return std::make_pair(y, x);
    }
}

int find_line(std::vector<ref::line>& L_list,int index_v0, int index_v1) {
    for (int i = 0; i < L_list.size(); i++)
    {
        if (L_list[i].v1 == min(index_v0,index_v1) && L_list[i].v2 == max(index_v0,index_v1))
        {
            return i;
        }   
    }
    return -1;
}

void ref::build_data_struct(
    std::vector < Eigen::Vector3f > out_vertices,
    std::vector < Eigen::Vector3f > out_normals,
    std::vector < int > out_v_index,
    std::vector < int > out_vn_index,
    std::vector<ref::point>& P_list,
    std::vector<ref::line>& L_list,
    std::vector<ref::face>& F_list,
    std::map<std::pair<int, int>, int>& dic)
{

    for (int i = 0; i < out_v_index.size(); i++) {
        int v_index = out_v_index[i];
        int vn_index = out_vn_index[i];
        P_list[v_index].pos = out_vertices[v_index];
        P_list[v_index].normal = out_normals[vn_index]; 
    }

    int index_cur_Face = 0;
    int line_index = 0;
    for (int i = 0; i < out_v_index.size(); i = i +3) {
        int index_v[3];
        index_v[0] = out_v_index[ i];
        index_v[1] = out_v_index[ i+1];
        index_v[2] = out_v_index[ i+2];

        F_list[index_cur_Face].v[0] = index_v[0];
        F_list[index_cur_Face].v[1] = index_v[1];
        F_list[index_cur_Face].v[2] = index_v[2];

        ref::line line1, line2, line3;
        int index_line[3];

        std::pair<int, int> pair_line_1 = line_point(index_v[0], index_v[1]);
        std::pair<int, int> pair_line_2 = line_point(index_v[0], index_v[2]);
        std::pair<int, int> pair_line_3 = line_point(index_v[1], index_v[2]);

        index_line[0] = find_line(L_list,index_v[0],index_v[1]);
        if (index_line[0] != -1) {
            L_list[index_line[0]].is_border = false;
        }
        else {
            index_line[0] = line_index;
            line_index++;
            line1.v1 = min(index_v[0], index_v[1]);
            line1.v2 = max(index_v[0], index_v[1]);
            L_list.push_back(line1);

            P_list[index_v[0]].n_point.push_back(index_v[1]);
            P_list[index_v[1]].n_point.push_back(index_v[0]);
            dic[pair_line_1] = index_line[0];
        }

        index_line[1] = find_line(L_list,index_v[0],index_v[2]);
        if (index_line[1] != -1) {
            L_list[index_line[1]].is_border = false;
        }
        else {
            index_line[1] = line_index;
            line_index++;
            line2.v1 = min(index_v[0], index_v[2]);
            line2.v2 = max(index_v[0], index_v[2]);
            L_list.push_back(line2);

            P_list[index_v[0]].n_point.push_back(index_v[2]);
            P_list[index_v[2]].n_point.push_back(index_v[0]);
            dic[pair_line_2] = index_line[1];
        }

        index_line[2] = find_line(L_list,index_v[1],index_v[2]);
        if (index_line[2] != -1) {
            L_list[index_line[2]].is_border = false;
        }
        else {
            index_line[2] = line_index;
            line_index++;
            line3.v1 = min(index_v[1], index_v[2]);
            line3.v2 = max(index_v[1], index_v[2]);
            L_list.push_back(line3);

            P_list[index_v[1]].n_point.push_back(index_v[2]);
            P_list[index_v[2]].n_point.push_back(index_v[1]);
            dic[pair_line_3] = index_line[2];
        }
        L_list[index_line[0]].n_face.push_back(index_cur_Face);
        L_list[index_line[1]].n_face.push_back(index_cur_Face);
        L_list[index_line[2]].n_face.push_back(index_cur_Face);

        index_cur_Face++;
    }

    for (int i = 0; i < L_list.size(); i++) {
        if (L_list[i].is_border) {
            P_list[L_list[i].v1].is_border = true;
            P_list[L_list[i].v2].is_border = true;
            P_list[L_list[i].v1].b_point.push_back(L_list[i].v2);
            P_list[L_list[i].v2].b_point.push_back(L_list[i].v1);
        }
    }
    return;
}

void even_points(std::vector<ref::point> P_list, std::vector<ref::point>& P_list_new)
{
    for (int i = 0; i < P_list.size(); i++) {
        ref::point p_even = ref::point();
        if (P_list[i].is_border) {
            p_even.pos = 0.125 * (P_list[P_list[i].b_point[0]].pos + P_list[P_list[i].b_point[1]].pos) + 0.75 * P_list[i].pos;
            p_even.normal = 0.125 * (P_list[P_list[i].b_point[0]].normal + P_list[P_list[i].b_point[1]].normal) + 0.75 * P_list[i].normal;
            p_even.normal.normalize();
            p_even.is_border = true;
        }
        else {
            int n = P_list[i].n_point.size();
            float beta = (0.625 - pow(0.375 + 0.25 * cos(2 * pi / n), 2)) / n;
            p_even.pos = (1 - n * beta) * P_list[i].pos;
            p_even.normal = (1 - n * beta) * P_list[i].normal;
            for (int j = 0; j < n; j++) {
                p_even.pos += beta * P_list[P_list[i].n_point[j]].pos;
                p_even.normal += beta * P_list[P_list[i].n_point[j]].normal;
            }
            p_even.normal.normalize();
            p_even.is_border = false;
        }
        P_list_new.push_back(p_even);
    }
}

int odd_points(std::vector<ref::point>& P_list,std::vector<ref::line>& L_list,std::vector<ref::face>& F_list,std::vector<ref::point>& P_list_new,int p1,int p2,int index_line_temp ) 
{
    int t1, t2, t3, t4, t5, t6;
    int new_index;
    if (L_list[index_line_temp].new_point) {
        new_index = L_list[index_line_temp].new_point_index;
    }
    else {
        ref::point new_point = ref::point();
        new_index = P_list_new.size();
            if (L_list[index_line_temp].is_border) {
                new_point.is_border = true;
                new_point.pos = 0.5 * P_list[p1].pos + 0.5 * P_list[p2].pos;
                new_point.normal = 0.5 * P_list[p1].normal + 0.5 * P_list[p2].normal;
                new_point.normal.normalize();
            }
            else {
                new_point.is_border = false;
                int t1 = F_list[L_list[index_line_temp].n_face[0]].v[0];
                int t2 = F_list[L_list[index_line_temp].n_face[0]].v[1];
                int t3 = F_list[L_list[index_line_temp].n_face[0]].v[2];
                int t4 = F_list[L_list[index_line_temp].n_face[1]].v[0];
                int t5 = F_list[L_list[index_line_temp].n_face[1]].v[1];
                int t6 = F_list[L_list[index_line_temp].n_face[1]].v[2];

                new_point.pos = 0.125 * (P_list[p1].pos + P_list[p2].pos+ P_list[t1].pos + P_list[t2].pos + P_list[t3].pos+ P_list[t4].pos + P_list[t5].pos + P_list[t6].pos);
                new_point.normal = 0.125 * (P_list[p1].normal + P_list[p2].normal+ P_list[t1].normal + P_list[t2].normal + P_list[t3].normal+ P_list[t4].normal + P_list[t5].normal + P_list[t6].normal);
                new_point.normal.normalize();
            }
        P_list_new.push_back(new_point);
        L_list[index_line_temp].new_point = true;
        L_list[index_line_temp].new_point_index = new_index;
    }
    return new_index;
}

int new_line(   std::vector<ref::point>& P_list_new,std::vector<ref::line>& L_list_new,std::map<std::pair<int, int>, int>& dic_new,int v1,int v2, bool is_border )
{
    int new_index = L_list_new.size();
    ref::line new_line;
    std::pair<int, int> new_line_pair = line_point(v1, v2);
    new_line.is_border = is_border;
    new_line.v1 = min(v1,v2);
    new_line.v2 = max(v1,v2);
    new_line.new_point = false;
    L_list_new.push_back(new_line);
    dic_new[new_line_pair] = new_index;
    return new_index;   
}

int new_face(std::vector<ref::face>& F_list_new, int p0, int p1, int p2) 
{
    int new_index = F_list_new.size();
    ref::face new_face;
    new_face.v[0] = p0;
    new_face.v[1] = p1;
    new_face.v[2] = p2;
    F_list_new.push_back(new_face);
    return new_index;
}

void info_complete(int line1, int line2, int line3, int line4, int line5, int line6,int line7,int line8,int line9,
                    std::vector<ref::point>& P_list_new,  std::vector<ref::line>& L_list_new, std::vector<ref::face>& F_list_new,
                    std::map<std::pair<int, int>, int>& dic_new,int v0_index,int v1_index,int v2_index,int v3_index,int v4_index,int v5_index)
{
    int face_034, face_135, face_245, face_345;
    face_034 = new_face(F_list_new, v0_index, v3_index, v4_index);
    face_135 = new_face(F_list_new, v1_index, v3_index, v5_index);
    face_245 = new_face(F_list_new, v2_index, v4_index, v5_index);
    face_345 = new_face(F_list_new, v3_index, v4_index, v5_index);

    L_list_new[line1].n_face.push_back(face_034);
    L_list_new[line2].n_face.push_back(face_034);
    L_list_new[line7].n_face.push_back(face_034);

    L_list_new[line3].n_face.push_back(face_135);
    L_list_new[line4].n_face.push_back(face_135);
    L_list_new[line8].n_face.push_back(face_135);

    L_list_new[line5].n_face.push_back(face_245);
    L_list_new[line6].n_face.push_back(face_245);
    L_list_new[line9].n_face.push_back(face_245);

    L_list_new[line7].n_face.push_back(face_345);
    L_list_new[line8].n_face.push_back(face_345);
    L_list_new[line9].n_face.push_back(face_345);
}

void ref::loop_subdivision(
    std::vector<ref::point> P_list,
    std::vector<ref::line> L_list,
    std::vector<ref::face> F_list,
    std::vector<ref::point>& P_list_new,
    std::vector<ref::line>& L_list_new,
    std::vector<ref::face>& F_list_new,
    std::map<std::pair<int, int>, int>& dic,
    std::map<std::pair<int, int>, int>& dic_new)
{
    even_points(P_list, P_list_new);
    
    for (int i = 0; i < F_list.size(); i++) {
        int v0_index = F_list[i].v[0];
        int v1_index = F_list[i].v[1];
        int v2_index = F_list[i].v[2];
        int v3_index, v4_index, v5_index;

        int index_line1 = find_line(L_list,v0_index, v1_index);
        int index_line2 = find_line(L_list,v0_index, v2_index);
        int index_line3 = find_line(L_list,v1_index, v2_index);

        bool line1_new, line2_new, line3_new;

        line1_new = L_list[index_line1].new_point;
        v3_index = odd_points(P_list, L_list, F_list, P_list_new, v0_index, v1_index, index_line1);

        line2_new = L_list[index_line2].new_point;
        v4_index = odd_points(P_list, L_list, F_list, P_list_new, v0_index, v2_index, index_line2);

        line3_new = L_list[index_line3].new_point;
        v5_index = odd_points(P_list, L_list, F_list, P_list_new, v1_index, v2_index, index_line3);

        int line1, line2, line3, line4, line5, line6,line7,line8,line9;

        if (line1_new) {
            line1 = find_line(L_list_new,v0_index, v3_index);
            line3 = find_line(L_list_new,v1_index, v3_index);
        }
        else {
            line1 = new_line(P_list_new,L_list_new, dic_new, v0_index, v3_index, L_list[index_line1].is_border);
            line3 = new_line(P_list_new,L_list_new, dic_new, v1_index, v3_index, L_list[index_line1].is_border);
        }

        if (line2_new) {
            line2 = find_line(L_list_new,v0_index, v4_index);
            line5 = find_line(L_list_new,v2_index, v4_index);
        }
        else {
            line2 = new_line(P_list_new, L_list_new, dic_new, v0_index, v4_index, L_list[index_line2].is_border);
            line5 = new_line(P_list_new, L_list_new, dic_new, v2_index, v4_index, L_list[index_line2].is_border);
        }

        if (line3_new) {
            line4 = find_line(L_list_new,v1_index, v5_index);
            line6 = find_line(L_list_new,v2_index, v5_index);
        }
        else {
            line4 = new_line(P_list_new, L_list_new, dic_new, v1_index, v5_index, L_list[index_line3].is_border);
            line6 = new_line(P_list_new, L_list_new, dic_new, v2_index, v5_index, L_list[index_line3].is_border);
        }

        line7 = new_line(P_list_new, L_list_new, dic_new, v3_index, v4_index, false);
        line8 = new_line(P_list_new, L_list_new, dic_new, v3_index, v5_index, false);
        line9 = new_line(P_list_new, L_list_new, dic_new, v4_index, v5_index, false);

        info_complete(line1, line2, line3, line4,  line5,  line6, line7, line8, line9, P_list_new,   L_list_new,  F_list_new,
                                        dic_new, v0_index, v1_index, v2_index, v3_index, v4_index, v5_index);
    }
    
    for (int i = 0; i < L_list_new.size(); i++) {
        P_list_new[L_list_new[i].v1].n_point.push_back(L_list_new[i].v2);
        P_list_new[L_list_new[i].v2].n_point.push_back(L_list_new[i].v1);
        if (L_list_new[i].is_border) {
            P_list_new[L_list_new[i].v1].b_point.push_back(L_list_new[i].v2);
            P_list_new[L_list_new[i].v2].b_point.push_back(L_list_new[i].v1);
            P_list_new[L_list_new[i].v1].is_border = true;
            P_list_new[L_list_new[i].v2].is_border = true;
        }

    }
    return;
}

void ref::make_face(
        std::vector<ref::point> P_list,
        std::vector<ref::face> F_list,
        std::vector<Eigen::Vector3f>& points, 
        std::vector<Eigen::Vector3f>& normals, 
        std::vector<Eigen::Vector2f>& uvs) 
{
	return;
}