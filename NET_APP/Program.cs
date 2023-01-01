var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.UseHttpLogging();

app.MapGet("/", (HttpRequest request, HttpResponse response) =>  response.WriteAsync("<h1>Hello World</h1>"));

app.Run();
