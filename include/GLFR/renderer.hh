#ifndef GLFR_RENDERER_HH
#define GLFR_RENDERER_HH

namespace glfr
{
	class Renderer
	{
	public:
		void Init(const int viewportWidth, const int viewportHeight);

		void ClearColor(const int r, const int g, const int b);
		void ClearColor(const int c);
		void ClearDepth();

	private:
	};
}

#endif
