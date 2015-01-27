// color 0 = red, 1 = green, 2 = yellow
struct VertexCell
{
    float x, y;
    float r,g,b;
	int color;
	VertexCell(){}
	VertexCell(int inX, int inY, int inR, int inG, int inB, int colorIN) : x(inX), y(inY), r(inR), g(inG), b(inB), color(colorIN){ }
	bool operator < (const VertexCell& other) const{
		return (x < other.x);
	}
	bool operator == (const VertexCell& other) const{
		return (x == other.x && y == other.y);
	}
	bool operator > (const VertexCell& other) const{
		return (x > other.x);
	}
};

struct sort_on_y
{
	inline bool operator() (const VertexCell& struct1, const VertexCell& struct2)
	{
		return (struct1.y < struct2.y);
	}
};

struct count_cancer
{
	inline bool operator() (const VertexCell& vc)
	{
		return (vc.color == 0);
	}
};

struct count_healthy
{
	inline bool operator() (const VertexCell& vc)
	{
		return (vc.color == 1);
	}
};

struct count_medicine
{
	inline bool operator() (const VertexCell& vc)
	{
		return (vc.color == 2);
	}
};
