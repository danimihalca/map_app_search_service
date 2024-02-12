using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;

namespace map_app_search_service.Controllers;

[ApiController]
[Route("[controller]")]
public class SearchController : ControllerBase
{
    private readonly ILogger<SearchController> _logger;
    private readonly HttpClient _httpClient;
    private readonly IOptions<SearchServiceOptions> _config;
    public SearchController(ILogger<SearchController> logger, HttpClient httpClient, IOptions<SearchServiceOptions> config)
    {
        _logger = logger;
        _httpClient = httpClient;
        _config = config;

        _logger.LogDebug("Controller created");
    }

    [HttpGet]
    [Route("places/{query}")]
    public String Get(String query, String proximity)
    {
        _logger.LogInformation(_config.Value.accessToken);
        var url = String.Format("{0}/{1}.json?access_token={2}&proximity={3}", 
            "https://api.mapbox.com/geocoding/v5/mapbox.places",
            query, _config.Value.accessToken, proximity);

        var result =_httpClient.GetAsync(url).Result;
 
        return result.Content.ReadAsStringAsync().Result;
    }
}
