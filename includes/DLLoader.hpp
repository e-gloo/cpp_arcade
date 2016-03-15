#ifndef DLLOADER_HPP
# define DLLOADER_HPP

template <typename T>
class DLLoader
{
private:
  void		*_handle;
public:
  explicit DLLoader();
  virtual ~DLLoader() {};
  T	*getInstance();
};

#endif
