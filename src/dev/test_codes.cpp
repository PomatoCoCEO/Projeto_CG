void print_vector_pts(vector<GLdouble> &vec)
{
    cout << "{";
    for (int i = 0; i < vec.size(); i += 3)
    {
        cout << vec[i] << "," << vec[i + 1] << "," << vec[i + 2] << "\n";
    }
    cout << "}\n";
}
template <typename T>
void print_vector(vector<T> &vec)
{
    cout << "{" << vec[0];
    for (int i = 1; i < vec.size(); i++)
        cout << "," << vec[i];
    cout << "}\n";
}

void startCuboid()
{
    point3d p = {0, 0, 0};
    vector<point3d> vec;
    GLdouble a = 1;

    vector<GLdouble> col = {1, 0, 1};
    for (int i = 0; i < (1 << 3); i++)
    {
        vector<GLdouble> ps = {0, 0, 0};
        int j = i;
        while (j > 0)
        {
            int k = LSOne(j);
            int pos = __builtin_ctz(k);
            ps[pos] += 1.0;
            j -= k;
        }
        /*for (size_t k = 0; k < ps.size(); k++)
            cuVertices.push_back(ps[i]), cuColours.push_back(col[i]);*/
        point3d p2 = point3d(ps[0], ps[1], ps[2]);

        vec.push_back(p2);
    }
    for (auto pi : vec)
    {
        cuVertices.push_back(pi.x);
        cuVertices.push_back(pi.y);
        cuVertices.push_back(pi.z);
        for (int i = 0; i < 3; i++)
        {
            cuColours.push_back(col[0]);
            cuColours.push_back(col[1]);
            cuColours.push_back(col[2]);
        }
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, &cuVertices[0]);
    glEnable(GL_COLOR_ARRAY);
    glColorPointer(3, GL_DOUBLE, 0, &cuColours[0]);
    cout << "Vertices are " << cuVertices.size() << "and colors are " << cuColours.size() << endl;
}

void drawCuboid()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, &cuVertices[0]);
    glEnable(GL_COLOR_ARRAY);
    glColorPointer(3, GL_DOUBLE, 0, &cuColours[0]);
    print_vector_pts(cuVertices);
    vec = {0, 1, 3, 2};
    print_vector(vec);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
    vec = {0, 2, 6, 4};
    print_vector(vec);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
    vec = {1, 3, 7, 5};
    print_vector(vec);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
    vec = {4, 5, 7, 6};
    print_vector(vec);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
    vec = {0, 1, 5, 4};
    print_vector(vec);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
    vec = {2, 3, 7, 6};
    print_vector(vec);
}