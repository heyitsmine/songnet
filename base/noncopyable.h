#ifndef SONG_BASE_NONCOPYABLE_H
#define SONG_BASE_NONCOPYABLE_H

namespace song
{

class noncopyable {
public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

} // namespace song

#endif // !SONG_BASE_NONCOPYABLE_H