from .some_responses import send_json_message

def allow_post(view_func):
  def wrapper(request, **kwargs):
    if request.method != "POST":
      return send_json_message("Method not Allowed")
    return view_func(request, **kwargs)
  return wrapper